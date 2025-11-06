#include <WiFi.h>
#include <HTTPClient.h>

// ========== CONFIGURACIÓN WIFI ==========
const char *ssid = "TU_SSID";         // ← Cambiar por tu WiFi
const char *password = "TU_PASSWORD"; // ← Cambiar por tu contraseña

// ========== CONFIGURACIÓN RESPIRA ==========
const char *respiraURL = "http://calidadmedioambiental.org/iot/d";
const char *apiKey = "TU_API_KEY_AQUI"; // ← API Key de tu PERFIL de dispositivo
const char *deviceID = "WEMOS_001";     // ← ID único para TU dispositivo (ej: WEMOS_CASA_01)

// ========== PINES DE SENSORES ==========
// Wemos Lolin32 tiene pines analógicos: 32, 33, 34, 35, 36, 39
#define MQ135_PIN 34 // Pin analógico para MQ-135
#define HYGRO_PIN 35 // Pin analógico para higrómetro

// ========== CALIBRACIÓN DE SENSORES ==========
// MQ-135: Valores calibrados
#define MQ135_MIN 300 // Valor mínimo aproximado (aire limpio)
#define MQ135_MAX 610 // Valor máximo detectado (aire contaminado)

// Higrómetro: Valores calibrados
#define HYGRO_DRY 238 // Valor cuando está seco (aire)
#define HYGRO_WET 206 // Valor cuando está en agua

// ========== VARIABLES GLOBALES ==========
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 60000; // Enviar cada 60 segundos

// ========== ESTRUCTURA DE DATOS ==========
struct SensorData
{
    int airQualityRaw;     // Valor crudo MQ-135
    float airQualityPPM;   // Convertido a PPM aproximado
    int soilMoistureRaw;   // Valor crudo higrómetro
    float soilMoisturePct; // Porcentaje de humedad
    bool valid;
};

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n╔════════════════════════════════════════╗");
    Serial.println("║  ESP32 Wemos Lolin32 - Respira IoT   ║");
    Serial.println("║  Higrómetro + MQ-135                  ║");
    Serial.println("╚════════════════════════════════════════╝\n");

    // Configurar pines analógicos
    initSensors();

    // Conectar WiFi
    connectWiFi();

    Serial.println("\n✓ Sistema listo!");
    Serial.println("→ Enviando datos cada 60 segundos\n");
}

void loop()
{
    // Verificar conexión WiFi
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("⚠ WiFi desconectado. Reconectando...");
        connectWiFi();
    }

    // Enviar datos según intervalo
    if (millis() - lastSendTime >= sendInterval)
    {
        SensorData data = readAllSensors();

        if (data.valid)
        {
            printSensorData(data);
            sendToRespira(data);
        }
        else
        {
            Serial.println("✗ Error al leer sensores");
        }

        lastSendTime = millis();
    }

    delay(1000);
}

// ========== INICIALIZACIÓN ==========
void initSensors()
{
    Serial.println("⚙ Inicializando sensores...");

    // Configurar resolución del ADC (12 bits = 0-4095)
    analogReadResolution(12);

    // Configurar atenuación para rango completo 0-3.3V
    analogSetAttenuation(ADC_11db);

    // Configurar pines como entrada
    pinMode(MQ135_PIN, INPUT);
    pinMode(HYGRO_PIN, INPUT);

    Serial.println("  ✓ MQ-135 en pin " + String(MQ135_PIN));
    Serial.println("  ✓ Higrómetro en pin " + String(HYGRO_PIN));

    // Pre-calentar MQ-135 (recomendado 24-48 horas, mínimo 1 minuto)
    Serial.println("\n⏳ Pre-calentando MQ-135 (20 segundos)...");
    for (int i = 20; i > 0; i--)
    {
        Serial.print("  " + String(i) + "s ");
        delay(1000);
    }
    Serial.println("\n✓ Sensores listos\n");
}

void connectWiFi()
{
    Serial.print("📡 Conectando a WiFi '" + String(ssid) + "'");
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\n✓ WiFi conectado");
        Serial.println("  IP: " + WiFi.localIP().toString());
        Serial.println("  RSSI: " + String(WiFi.RSSI()) + " dBm");
    }
    else
    {
        Serial.println("\n✗ No se pudo conectar a WiFi");
        Serial.println("  Revisa SSID y contraseña");
    }
}

// ========== LECTURA DE SENSORES ==========
SensorData readAllSensors()
{
    SensorData data;
    data.valid = true;

    // ===== Leer MQ-135 (Calidad del aire) =====
    // Tomar varias muestras para mayor precisión
    long mq135Sum = 0;
    const int samples = 10;

    for (int i = 0; i < samples; i++)
    {
        mq135Sum += analogRead(MQ135_PIN);
        delay(10);
    }

    data.airQualityRaw = mq135Sum / samples;

    // Convertir a PPM aproximado (fórmula simplificada)
    // Nota: Para calibración precisa se necesita gas de referencia
    data.airQualityPPM = map(data.airQualityRaw, MQ135_MIN, MQ135_MAX, 0, 500);

    // ===== Leer Higrómetro (Humedad del suelo) =====
    // Tomar varias muestras
    long hygroSum = 0;

    for (int i = 0; i < samples; i++)
    {
        hygroSum += analogRead(HYGRO_PIN);
        delay(10);
    }

    data.soilMoistureRaw = hygroSum / samples;

    // Convertir a porcentaje (0% = seco, 100% = mojado)
    // Invertir porque valores altos = seco, valores bajos = mojado
    data.soilMoisturePct = map(data.soilMoistureRaw, HYGRO_DRY, HYGRO_WET, 0, 100);

    // Limitar entre 0-100%
    if (data.soilMoisturePct < 0)
        data.soilMoisturePct = 0;
    if (data.soilMoisturePct > 100)
        data.soilMoisturePct = 100;

    return data;
}

void printSensorData(SensorData data)
{
    Serial.println("╔══════════════════════════════════════════╗");
    Serial.println("║          LECTURA DE SENSORES             ║");
    Serial.println("╠══════════════════════════════════════════╣");

    // MQ-135
    Serial.println("║ 🌫  MQ-135 (Calidad del Aire)");
    Serial.println("║   → Valor RAW: " + String(data.airQualityRaw) + " / 4095");
    Serial.println("║   → PPM aprox: " + String(data.airQualityPPM, 0));
    Serial.print("║   → Estado: ");

    if (data.airQualityPPM < 50)
    {
        Serial.println("Excelente ✓");
    }
    else if (data.airQualityPPM < 100)
    {
        Serial.println("Bueno");
    }
    else if (data.airQualityPPM < 200)
    {
        Serial.println("Moderado ⚠");
    }
    else
    {
        Serial.println("Malo ✗");
    }

    Serial.println("║");

    // Higrómetro
    Serial.println("║ 💧 Higrómetro (Humedad del Suelo)");
    Serial.println("║   → Valor RAW: " + String(data.soilMoistureRaw) + " / 4095");
    Serial.println("║   → Humedad: " + String(data.soilMoisturePct, 1) + "%");
    Serial.print("║   → Estado: ");

    if (data.soilMoisturePct < 20)
    {
        Serial.println("Muy seco ✗");
    }
    else if (data.soilMoisturePct < 40)
    {
        Serial.println("Seco");
    }
    else if (data.soilMoisturePct < 70)
    {
        Serial.println("Óptimo ✓");
    }
    else
    {
        Serial.println("Muy húmedo");
    }

    Serial.println("╚══════════════════════════════════════════╝\n");
}

// ========== ENVÍO A RESPIRA ==========
void sendToRespira(SensorData data)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("✗ No hay conexión WiFi");
        return;
    }

    HTTPClient http;

    // Construir URL con parámetros
    String url = String(respiraURL) + "?k=" + apiKey + "&i=" + deviceID;

    // Construir el BODY en formato texto plano
    // no2 = Calidad del aire (PPM del MQ-135)
    // h = Humedad (del suelo en este caso, porcentaje)
    String body = "no2|" + String(data.airQualityPPM, 1) +
                  "|h|" + String(data.soilMoisturePct, 1);

    Serial.println("📤 Enviando a Respira...");
    Serial.println("   URL: " + url);
    Serial.println("   Body: " + body);

    http.begin(url);
    http.addHeader("Content-Type", "text/plain");
    http.setTimeout(10000); // Timeout de 10 segundos

    int httpCode = http.POST(body);

    if (httpCode > 0)
    {
        Serial.print("   Respuesta HTTP: ");
        Serial.println(httpCode);

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_NO_CONTENT)
        {
            Serial.println("   ✓ Datos enviados correctamente");

            String response = http.getString();
            if (response.length() > 0)
            {
                Serial.println("   Respuesta: " + response);
            }
        }
        else if (httpCode == 400)
        {
            Serial.println("   ✗ Error 400: Verifica el Device ID y formato");
        }
        else if (httpCode == 401)
        {
            Serial.println("   ✗ Error 401: API Key incorrecta");
        }
        else if (httpCode == 404)
        {
            Serial.println("   ✗ Error 404: Device ID no existe");
        }
        else
        {
            String response = http.getString();
            Serial.println("   ⚠ Respuesta inesperada: " + response);
        }
    }
    else
    {
        Serial.print("   ✗ Error en petición HTTP: ");
        Serial.println(http.errorToString(httpCode));
    }

    http.end();
    Serial.println();
}

// ========== FUNCIÓN DE CALIBRACIÓN (Opcional) ==========
// Llama a esta función desde setup() para calibrar sensores
void calibrateSensors()
{
    Serial.println("\n╔════════════════════════════════════════╗");
    Serial.println("║     MODO CALIBRACIÓN DE SENSORES      ║");
    Serial.println("╚════════════════════════════════════════╝\n");

    Serial.println("📍 CALIBRACIÓN HIGRÓMETRO:");
    Serial.println("1. Saca el sensor del suelo (aire seco)");
    Serial.println("   Espera 10 segundos...");
    delay(10000);

    int dryValue = analogRead(HYGRO_PIN);
    Serial.println("   ✓ Valor SECO: " + String(dryValue));

    Serial.println("\n2. Mete el sensor en agua");
    Serial.println("   Espera 10 segundos...");
    delay(10000);

    int wetValue = analogRead(HYGRO_PIN);
    Serial.println("   ✓ Valor MOJADO: " + String(wetValue));

    Serial.println("\n📝 Actualiza estas constantes en el código:");
    Serial.println("   #define HYGRO_DRY " + String(dryValue));
    Serial.println("   #define HYGRO_WET " + String(wetValue));
    Serial.println("\n");
}