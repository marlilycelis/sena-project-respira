---
layout: home
title: Inicio
nav_order: 1
description: "Sistema IoT de monitoreo ambiental desarrollado en el SENA"
permalink: /
---

# 🌿 Proyecto Respira – Monitoreo Ambiental IoT
{: .fs-9 }

Sistema de monitoreo de calidad del aire y humedad del suelo mediante sensores conectados a ESP32 Wemos Lolin32.
{: .fs-6 .fw-300 }

[Ver código en GitHub](https://github.com/marlilycelis/sena-proyecto-respira){: .btn .btn-primary .fs-5 .mb-4 .mb-md-0 .mr-2 }
[Ver datos en vivo](https://www.calidadmedioambiental.org/dashboard){: .btn .fs-5 .mb-4 .mb-md-0 }

---

## 🎯 Objetivo general

Diseñar e implementar un sistema IoT capaz de monitorear la calidad del aire y la humedad del suelo, enviando los datos en tiempo real a la plataforma **Respira** para su análisis y visualización.

---

## 🧩 Navegación rápida

<div class="code-example" markdown="1">

### Documentación técnica

- [⚙️ Componentes utilizados](componentes) - Hardware y software del proyecto
- [🔌 Conexiones eléctricas](conexiones) - Diagramas y esquemas de conexión
- [💻 Código fuente](codigo) - Programación y calibración

### Información del proyecto

- [👥 Autores](autores) - Equipo de desarrollo
- [📄 Licencia](licencia) - Términos de uso

</div>

---

## 🌎 Visualización de datos en tiempo real

Accede al panel de tu dispositivo en la plataforma **Respira IoT**.

{: .note }
> 📍 **Ubicación del dispositivo:** WEMOS_001_SENA_PASTO
>
> Busca este identificador en el selector de dispositivos del dashboard.

[🌍 Abrir panel de datos Respira](https://www.calidadmedioambiental.org/dashboard){: .btn .btn-green }

{: .warning }
> ⚠ **Nota importante:** La visualización directa de datos históricos desde la API pública fue deshabilitada temporalmente. Los valores se pueden consultar desde la interfaz web o mediante descarga manual.

---

## 📊 Características del sistema

| Característica | Descripción |
|:---------------|:------------|
| **Plataforma** | ESP32 Wemos Lolin32 |
| **Conectividad** | WiFi 2.4GHz |
| **Sensores** | MQ-135 (calidad aire) + Higrómetro (humedad suelo) |
| **Transmisión** | HTTP a plataforma Respira |
| **Alimentación** | 5V USB o batería |

---

## 🚀 Inicio rápido

1. **Revisa los [componentes necesarios](componentes)**
2. **Realiza las [conexiones eléctricas](conexiones)**
3. **Carga el [código de calibración](codigo)**
4. **Configura y carga el [código principal](codigo)**
5. **Visualiza tus datos en tiempo real**

---

## 📚 Recursos adicionales

- [Documentación oficial Respira](https://panstamp.github.io/respira_fiware/)
- [Plataforma Respira](http://calidadmedioambiental.org)
- [Arduino IDE](https://www.arduino.cc/en/software)

---

<div class="code-example" markdown="1">
**Proyecto desarrollado en el SENA** - Centro de Formación Pasto, Nariño
</div>