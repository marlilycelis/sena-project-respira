/*
 * PROGRAMA DE CALIBRACIÓN DE SENSORES
 * ESP32 Wemos Lolin32
 * - MQ-135 (Calidad del aire)
 * - Higrómetro Resistivo (Humedad del suelo)
 *
 * INSTRUCCIONES:
 * 1. Conecta los sensores según el diagrama
 * 2. Sube este código al ESP32
 * 3. Abre el Monitor Serial a 115200 baud
 * 4. Sigue las instrucciones en pantalla
 * 5. Anota los valores finales para actualizar el código principal
 */

// ========== PINES DE SENSORES ==========
#define MQ135_PIN 34 // Pin analógico para MQ-135
#define HYGRO_PIN 35 // Pin analógico para higrómetro

// ========== VARIABLES GLOBALES ==========
int mq135_baseline = 0; // Línea base MQ-135 (aire limpio)
int mq135_max = 0;      // Valor máximo MQ-135
int hygro_dry = 0;      // Higrómetro en aire (seco)
int hygro_wet = 0;      // Higrómetro en agua (mojado)

void setup()
{
  Serial.begin(115200);
  delay(2000);

  // Configurar ADC
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  pinMode(MQ135_PIN, INPUT);
  pinMode(HYGRO_PIN, INPUT);

  mostrarBanner();
  menuPrincipal();
}

void loop()
{
  // Todo el proceso es interactivo desde el menú
  delay(100);
}

// ========== BANNER INICIAL ==========
void mostrarBanner()
{
  Serial.println("\n\n");
  Serial.println("╔═══════════════════════════════════════════════════╗");
  Serial.println("║                                                   ║");
  Serial.println("║     CALIBRACIÓN DE SENSORES - WEMOS LOLIN32      ║");
  Serial.println("║                                                   ║");
  Serial.println("║  MQ-135: GPIO 34                                 ║");
  Serial.println("║  Higrómetro: GPIO 35                             ║");
  Serial.println("║                                                   ║");
  Serial.println("╚═══════════════════════════════════════════════════╝");
  Serial.println();
}

// ========== MENÚ PRINCIPAL ==========
void menuPrincipal()
{
  while (true)
  {
    Serial.println("\n╔════════════════ MENÚ PRINCIPAL ═══════════════════╗");
    Serial.println("║                                                   ║");
    Serial.println("║  1. Lectura continua de sensores (modo monitor)  ║");
    Serial.println("║  2. Calibrar MQ-135 (sensor de gas/aire)         ║");
    Serial.println("║  3. Calibrar Higrómetro (humedad del suelo)      ║");
    Serial.println("║  4. Mostrar valores de calibración guardados     ║");
    Serial.println("║  5. Generar código para copiar                   ║");
    Serial.println("║                                                   ║");
    Serial.println("╚═══════════════════════════════════════════════════╝");
    Serial.println("\nEscribe el número de opción y presiona ENTER:");

    esperarOpcion();
  }
}

void esperarOpcion()
{
  while (!Serial.available())
  {
    delay(100);
  }

  char opcion = Serial.read();
  // Limpiar buffer
  while (Serial.available())
    Serial.read();

  Serial.println("\n→ Opción seleccionada: " + String(opcion));
  Serial.println();

  switch (opcion)
  {
  case '1':
    modoMonitor();
    break;
  case '2':
    calibrarMQ135();
    break;
  case '3':
    calibrarHigrometro();
    break;
  case '4':
    mostrarValores();
    break;
  case '5':
    generarCodigo();
    break;
  default:
    Serial.println("✗ Opción inválida. Intenta de nuevo.");
    break;
  }
}

// ========== MODO MONITOR ==========
void modoMonitor()
{
  Serial.println("╔════════════════ MODO MONITOR ═════════════════════╗");
  Serial.println("║  Lecturas en tiempo real cada 2 segundos         ║");
  Serial.println("║  Presiona cualquier tecla + ENTER para salir    ║");
  Serial.println("╚═══════════════════════════════════════════════════╝\n");

  delay(2000);

  while (!Serial.available())
  {
    int mq135 = leerSensorPromedio(MQ135_PIN, 10);
    int hygro = leerSensorPromedio(HYGRO_PIN, 10);

    Serial.println("┌──────────────────────────────────────────────────┐");
    Serial.printf("│ MQ-135 (GPIO 34):     %4d / 4095  [", mq135);
    imprimirBarraProgreso(mq135, 4095, 20);
    Serial.println("]");

    Serial.printf("│ Higrómetro (GPIO 35): %4d / 4095  [", hygro);
    imprimirBarraProgreso(hygro, 4095, 20);
    Serial.println("]");
    Serial.println("└──────────────────────────────────────────────────┘\n");

    delay(2000);
  }

  // Limpiar buffer
  while (Serial.available())
    Serial.read();
  Serial.println("\n✓ Saliendo del modo monitor...\n");
}

// ========== CALIBRACIÓN MQ-135 ==========
void calibrarMQ135()
{
  Serial.println("╔═══════════════════════════════════════════════════╗");
  Serial.println("║         CALIBRACIÓN DEL SENSOR MQ-135            ║");
  Serial.println("╚═══════════════════════════════════════════════════╝\n");

  Serial.println("📌 IMPORTANTE: El MQ-135 necesita pre-calentamiento");
  Serial.println("   Idealmente 24-48 horas, mínimo 20-30 minutos\n");

  Serial.println("¿Ya pre-calentaste el sensor?");
  Serial.println("  S = Sí, continuar");
  Serial.println("  N = No, hacer pre-calentamiento ahora (5 min)");
  Serial.print("\nOpción: ");

  char respuesta = esperarCaracter();

  if (respuesta == 'N' || respuesta == 'n')
  {
    precalentarMQ135();
  }

  // PASO 1: Aire limpio (baseline)
  Serial.println("\n╔═══════════════════════════════════════════════════╗");
  Serial.println("║ PASO 1: CALIBRACIÓN EN AIRE LIMPIO               ║");
  Serial.println("╚═══════════════════════════════════════════════════╝\n");

  Serial.println("📍 Coloca el sensor MQ-135 en un lugar con:");
  Serial.println("   • Aire fresco y limpio");
  Serial.println("   • Lejos de cocinas, baños, humos");
  Serial.println("   • Ventilación normal");
  Serial.println("\n⏳ Espera 2 minutos para estabilizar...\n");

  Serial.println("Presiona ENTER cuando esté listo...");
  esperarEnter();

  Serial.println("\n🔍 Tomando 30 muestras en 30 segundos...\n");

  long suma = 0;
  int minVal = 4095;
  int maxVal = 0;

  for (int i = 1; i <= 30; i++)
  {
    int lectura = leerSensorPromedio(MQ135_PIN, 5);
    suma += lectura;

    if (lectura < minVal)
      minVal = lectura;
    if (lectura > maxVal)
      maxVal = lectura;

    Serial.printf("  Muestra %2d/30: %4d  [", i, lectura);
    imprimirBarraProgreso(i, 30, 15);
    Serial.println("]");

    delay(1000);
  }

  mq135_baseline = suma / 30;

  Serial.println("\n✓ Calibración en aire limpio completada:");
  Serial.println("  ├─ Promedio: " + String(mq135_baseline));
  Serial.println("  ├─ Mínimo:   " + String(minVal));
  Serial.println("  └─ Máximo:   " + String(maxVal));

  // PASO 2: Aire contaminado (opcional)
  Serial.println("\n╔═══════════════════════════════════════════════════╗");
  Serial.println("║ PASO 2: CALIBRACIÓN CON AIRE CONTAMINADO (Opc.)  ║");
  Serial.println("╚═══════════════════════════════════════════════════╝\n");

  Serial.println("¿Quieres calibrar el valor máximo con aire contaminado?");
  Serial.println("(Puedes soplar cerca del sensor o usar alcohol)");
  Serial.println("\n  S = Sí");
  Serial.println("  N = No, usar valor por defecto (4095)");
  Serial.print("\nOpción: ");

  respuesta = esperarCaracter();

  if (respuesta == 'S' || respuesta == 's')
  {
    Serial.println("\n📍 Expón el sensor a aire contaminado:");
    Serial.println("   • Sopla suavemente cerca del sensor, o");
    Serial.println("   • Acerca alcohol, perfume, o limpiador");
    Serial.println("\nPresiona ENTER cuando esté expuesto...");
    esperarEnter();

    Serial.println("\n🔍 Tomando 10 muestras...\n");

    int maxContaminado = 0;
    for (int i = 1; i <= 10; i++)
    {
      int lectura = leerSensorPromedio(MQ135_PIN, 5);
      if (lectura > maxContaminado)
        maxContaminado = lectura;

      Serial.printf("  Muestra %2d/10: %4d\n", i, lectura);
      delay(500);
    }

    mq135_max = maxContaminado;
    Serial.println("\n✓ Valor máximo detectado: " + String(mq135_max));
  }
  else
  {
    mq135_max = 4095;
    Serial.println("\n✓ Usando valor máximo por defecto: 4095");
  }

  Serial.println("\n╔═══════════════════════════════════════════════════╗");
  Serial.println("║       ✓ CALIBRACIÓN MQ-135 COMPLETADA            ║");
  Serial.println("╚═══════════════════════════════════════════════════╝");
  Serial.println("\n  Baseline (aire limpio): " + String(mq135_baseline));
  Serial.println("  Máximo (contaminado):   " + String(mq135_max));
  Serial.println();

  esperarContinuar();
}

// ========== CALIBRACIÓN HIGRÓMETRO ==========
void calibrarHigrometro()
{
  Serial.println("╔═══════════════════════════════════════════════════╗");
  Serial.println("║       CALIBRACIÓN DEL HIGRÓMETRO RESISTIVO       ║");
  Serial.println("╚═══════════════════════════════════════════════════╝\n");

  // PASO 1: Aire (seco)
  Serial.println("╔═══════════════════════════════════════════════════╗");
  Serial.println("║ PASO 1: CALIBRACIÓN EN SECO (AIRE)               ║");
  Serial.println("╚═══════════════════════════════════════════════════╝\n");

  Serial.println("📍 SACA el higrómetro de la tierra/agua");
  Serial.println("   Déjalo al aire libre (completamente seco)");
  Serial.println("\n⏳ Espera 1 minuto para que se seque...\n");

  Serial.println("Presiona ENTER cuando esté al aire (seco)...");
  esperarEnter();

  Serial.println("\n🔍 Tomando 20 muestras...\n");

  long sumaSeco = 0;
  int minSeco = 4095;
  int maxSeco = 0;

  for (int i = 1; i <= 20; i++)
  {
    int lectura = leerSensorPromedio(HYGRO_PIN, 5);
    sumaSeco += lectura;

    if (lectura < minSeco)
      minSeco = lectura;
    if (lectura > maxSeco)
      maxSeco = lectura;

    Serial.printf("  Muestra %2d/20: %4d  [", i, lectura);
    imprimirBarraProgreso(i, 20, 15);
    Serial.println("]");

    delay(500);
  }

  hygro_dry = sumaSeco / 20;

  Serial.println("\n✓ Calibración en seco completada:");
  Serial.println("  ├─ Promedio: " + String(hygro_dry));
  Serial.println("  ├─ Mínimo:   " + String(minSeco));
  Serial.println("  └─ Máximo:   " + String(maxSeco));

  // PASO 2: Agua (mojado)
  Serial.println("\n╔═══════════════════════════════════════════════════╗");
  Serial.println("║ PASO 2: CALIBRACIÓN EN MOJADO (AGUA)             ║");
  Serial.println("╚═══════════════════════════════════════════════════╝\n");

  Serial.println("📍 METE el higrómetro en un vaso con agua");
  Serial.println("   ⚠ Solo las puntas metálicas, NO la electrónica");
  Serial.println("   Profundidad: 2-3 cm aproximadamente");
  Serial.println("\nPresiona ENTER cuando esté en el agua...");
  esperarEnter();

  Serial.println("\n🔍 Tomando 20 muestras...\n");

  long sumaMojado = 0;
  int minMojado = 4095;
  int maxMojado = 0;

  for (int i = 1; i <= 20; i++)
  {
    int lectura = leerSensorPromedio(HYGRO_PIN, 5);
    sumaMojado += lectura;

    if (lectura < minMojado)
      minMojado = lectura;
    if (lectura > maxMojado)
      maxMojado = lectura;

    Serial.printf("  Muestra %2d/20: %4d  [", i, lectura);
    imprimirBarraProgreso(i, 20, 15);
    Serial.println("]");

    delay(500);
  }

  hygro_wet = sumaMojado / 20;

  Serial.println("\n✓ Calibración en mojado completada:");
  Serial.println("  ├─ Promedio: " + String(hygro_wet));
  Serial.println("  ├─ Mínimo:   " + String(minMojado));
  Serial.println("  └─ Máximo:   " + String(maxMojado));

  Serial.println("\n╔═══════════════════════════════════════════════════╗");
  Serial.println("║      ✓ CALIBRACIÓN HIGRÓMETRO COMPLETADA         ║");
  Serial.println("╚═══════════════════════════════════════════════════╝");
  Serial.println("\n  Seco (aire):      " + String(hygro_dry));
  Serial.println("  Mojado (agua):    " + String(hygro_wet));
  Serial.println("  Diferencia:       " + String(hygro_dry - hygro_wet));
  Serial.println();

  esperarContinuar();
}

// ========== MOSTRAR VALORES GUARDADOS ==========
void mostrarValores()
{
  Serial.println("╔═══════════════════════════════════════════════════╗");
  Serial.println("║        VALORES DE CALIBRACIÓN ACTUALES            ║");
  Serial.println("╚═══════════════════════════════════════════════════╝\n");

  Serial.println("📊 MQ-135 (Calidad del Aire):");
  if (mq135_baseline > 0)
  {
    Serial.println("  ✓ Baseline (aire limpio): " + String(mq135_baseline));
    Serial.println("  ✓ Máximo (contaminado):   " + String(mq135_max));
  }
  else
  {
    Serial.println("  ✗ No calibrado");
  }

  Serial.println("\n💧 Higrómetro (Humedad del Suelo):");
  if (hygro_dry > 0)
  {
    Serial.println("  ✓ Seco (aire):   " + String(hygro_dry));
    Serial.println("  ✓ Mojado (agua): " + String(hygro_wet));
  }
  else
  {
    Serial.println("  ✗ No calibrado");
  }

  Serial.println();
  esperarContinuar();
}

// ========== GENERAR CÓDIGO PARA COPIAR ==========
void generarCodigo()
{
  Serial.println("╔═══════════════════════════════════════════════════╗");
  Serial.println("║     CÓDIGO PARA COPIAR AL PROGRAMA PRINCIPAL     ║");
  Serial.println("╚═══════════════════════════════════════════════════╝\n");

  if (mq135_baseline == 0 && hygro_dry == 0)
  {
    Serial.println("⚠ No hay valores calibrados aún.");
    Serial.println("  Primero calibra los sensores (opciones 2 y 3).\n");
    esperarContinuar();
    return;
  }

  Serial.println("📋 Copia estas líneas en tu código principal:\n");
  Serial.println("// ========== CALIBRACIÓN DE SENSORES ==========");

  if (mq135_baseline > 0)
  {
    Serial.println("// MQ-135: Valores calibrados");
    Serial.println("#define MQ135_MIN " + String(mq135_baseline) + "  // Aire limpio");
    Serial.println("#define MQ135_MAX " + String(mq135_max) + "      // Máximo detectado");
  }

  if (hygro_dry > 0)
  {
    Serial.println("\n// Higrómetro: Valores calibrados");
    Serial.println("#define HYGRO_DRY " + String(hygro_dry) + "  // Sensor en aire (seco)");
    Serial.println("#define HYGRO_WET " + String(hygro_wet) + "  // Sensor en agua (mojado)");
  }

  Serial.println("\n✓ Reemplaza las constantes en tu código con estos valores.\n");

  esperarContinuar();
}

// ========== FUNCIONES AUXILIARES ==========

int leerSensorPromedio(int pin, int muestras)
{
  long suma = 0;
  for (int i = 0; i < muestras; i++)
  {
    suma += analogRead(pin);
    delay(10);
  }
  return suma / muestras;
}

void imprimirBarraProgreso(int actual, int total, int ancho)
{
  int progreso = (actual * ancho) / total;
  for (int i = 0; i < ancho; i++)
  {
    if (i < progreso)
      Serial.print("█");
    else
      Serial.print("░");
  }
}

char esperarCaracter()
{
  while (!Serial.available())
  {
    delay(100);
  }
  char c = Serial.read();
  while (Serial.available())
    Serial.read(); // Limpiar buffer
  Serial.println(c);
  return c;
}

void esperarEnter()
{
  while (!Serial.available())
  {
    delay(100);
  }
  while (Serial.available())
    Serial.read(); // Limpiar buffer
}

void esperarContinuar()
{
  Serial.println("Presiona ENTER para continuar...");
  esperarEnter();
}

void precalentarMQ135()
{
  Serial.println("\n⏳ Pre-calentando MQ-135 durante 5 minutos...");
  Serial.println("   (Idealmente debería ser 24-48 horas)\n");

  for (int minuto = 5; minuto > 0; minuto--)
  {
    Serial.print("  " + String(minuto) + " minuto(s) restante(s)... ");

    for (int seg = 60; seg > 0; seg--)
    {
      if (seg % 10 == 0)
        Serial.print(".");
      delay(1000);
    }
    Serial.println(" ✓");
  }

  Serial.println("\n✓ Pre-calentamiento básico completado\n");
  delay(1000);
}