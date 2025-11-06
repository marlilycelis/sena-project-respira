# 💻 Código del proyecto

El sistema se desarrolló en **Arduino IDE** utilizando dos programas principales:

1. **`calibracion.ino`** → Para calibrar los sensores MQ-135 y Higrómetro.  
2. **`respira_codigo.ino`** → Código final que envía los datos a la plataforma Respira.

---

## 🧠 Calibración de sensores

Este código permite obtener los valores mínimos y máximos de cada sensor (aire limpio / aire contaminado, seco / húmedo).

🔗 [Ver código completo de calibración (`calibracion.ino`)](https://github.com/marlilycelis/sena-proyecto-respira/blob/main/src/calibracion.ino)

---

## 🌐 Código principal: conexión con Respira

Este programa configura la red WiFi, lee los sensores y envía los datos a la plataforma Respira mediante HTTP.

🔗 [Ver código principal (`respira_codigo.ino`)](https://github.com/marlilycelis/sena-proyecto-respira/blob/main/src/respira_codigo.ino)

---

## 🔄 Flujo general del sistema

A continuación se muestra el flujo completo del proceso de captura, calibración y envío de datos del proyecto **Respira IoT**.

```mermaid
graph TD
    A[Inicio del ESP32] --> B[Conexión WiFi]
    B --> C[Lectura de sensores MQ-135 y Higrómetro]
    C --> D[Calibración o procesamiento de datos]
    D --> E[Envío a plataforma Respira]
    E --> F[Visualización de datos en la web]

