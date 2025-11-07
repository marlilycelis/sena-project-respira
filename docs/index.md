---
layout: default
title: Inicio
nav_order: 1
description: "Sistema IoT de monitoreo ambiental desarrollado en el SENA"
permalink: /
---

# Proyecto Respira
{: .fs-9 }

Monitoreo Ambiental IoT
{: .fs-6 .fw-300 }

[Ver en GitHub](https://github.com/marlilycelis/sena-project-respira){: .btn .btn-primary .fs-5 .mb-4 .mb-md-0 .mr-2 }
[Dashboard Respira](https://www.calidadmedioambiental.org/dashboard){: .btn .fs-5 .mb-4 .mb-md-0 }

---

## 🎯 Objetivo del proyecto

Diseñar e implementar un sistema IoT capaz de monitorear la calidad del aire y la humedad del suelo, enviando los datos en tiempo real a la plataforma **Respira** para su análisis y visualización.

El sistema utiliza:
- 🔧 **ESP32 Wemos Lolin32** como placa principal
- 🌡️ **Sensor MQ-135** para calidad del aire
- 💧 **Sensor Higrómetro** para humedad del suelo
- 📡 **Conexión WiFi** para envío de datos

---

## 📚 Documentación

| Sección | Descripción |
|:--------|:------------|
| [⚙️ Componentes](componentes) | Hardware y software utilizado |
| [🔌 Conexiones](conexiones) | Diagramas y esquemas eléctricos |
| [💻 Código](codigo) | Programación y calibración |
| [👥 Autores](autores) | Equipo de desarrollo |
| [📄 Licencia](licencia) | Términos de uso MIT |

---

## 🌍 Visualización en tiempo real

Puedes ver los datos de tu dispositivo en el dashboard de Respira:

{: .note }
**Identificador del dispositivo:** WEMOS_001_SENA_PASTO
> 
> Busca este código en el selector de dispositivos del dashboard.

[🌍 Abrir Dashboard](https://www.calidadmedioambiental.org/dashboard){: .btn .btn-green }

{: .warning }
La API pública de datos históricos está temporalmente deshabilitada. Los datos se pueden consultar desde la interfaz web.

---

## 🚀 Inicio rápido

1. Revisa los [componentes necesarios](componentes)
2. Realiza las [conexiones eléctricas](conexiones)
3. Carga el [código de calibración](codigo)
4. Configura y carga el [código principal](codigo)
5. Visualiza tus datos en tiempo real

---

## 📊 Características técnicas

| Característica | Especificación |
|:---------------|:---------------|
| **Microcontrolador** | ESP32 Dual-Core 240MHz |
| **Conectividad** | WiFi 802.11 b/g/n |
| **Sensores** | MQ-135 + Higrómetro |
| **Protocolo** | HTTP REST |
| **Intervalo** | 5 minutos |
| **Alimentación** | 5V USB |

---

## 🔗 Enlaces útiles

- [Documentación Respira](https://panstamp.github.io/respira_fiware/)
- [Plataforma Respira](http://calidadmedioambiental.org)
- [Arduino IDE](https://www.arduino.cc/en/software)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)

---

Proyecto desarrollado en el **SENA** - Centro Internacional de Producción Limpia Lope  
Pasto, Nariño, Colombia - 2025