---
layout: default
title: Componentes
nav_order: 2
description: "Lista completa de hardware y software utilizado"
---

# ⚙️ Componentes del sistema
{: .no_toc }

Lista detallada de todos los componentes electrónicos y herramientas de software utilizados en el proyecto.
{: .fs-6 .fw-300 }

## Tabla de contenidos
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## 🧠 Electrónica principal

### ESP32 Wemos Lolin32

**Microcontrolador principal del proyecto**

| Especificación | Valor |
|:--------------|:------|
| **Modelo** | ESP32 Wemos Lolin32 |
| **Procesador** | Dual-core 240MHz |
| **WiFi** | 802.11 b/g/n 2.4GHz |
| **Voltaje** | 3.3V lógica / 5V alimentación |
| **Pines ADC** | 18 canales de 12 bits |
| **Cantidad** | 1 |

![ESP32 Wemos Lolin32](assets/Lolin32.jpg)

{: .note }
Esta placa incluye WiFi integrado, ideal para proyectos IoT.

---

### Sensor MQ-135

**Sensor de calidad del aire**

| Especificación | Valor |
|:--------------|:------|
| **Tipo** | Sensor de gases MQ-135 |
| **Detecta** | CO₂, NH₃, NOₓ, alcohol, humo |
| **Voltaje** | 5V |
| **Salida** | Analógica |
| **Tiempo de calentamiento** | ~24 horas (óptimo) |
| **Cantidad** | 1 |

![Sensor MQ-135](assets/MQ135.png)

{: .important }
> **Calibración necesaria:** Este sensor requiere un período de calentamiento y calibración para lecturas precisas. Ver [código de calibración](codigo).

---

### Sensor Higrómetro

**Sensor de humedad del suelo**

| Especificación | Valor |
|:--------------|:------|
| **Tipo** | Higrómetro capacitivo/resistivo |
| **Mide** | Humedad del suelo |
| **Voltaje** | 3.3V - 5V |
| **Salida** | Analógica |
| **Cantidad** | 1 |

![Sensor Higrómetro](assets/Higrometro.jpg)

{: .warning }
Evita sumergir completamente el sensor. Solo la parte de las pistas debe estar en contacto con la tierra.

---

## 🔌 Componentes electrónicos auxiliares

### Resistencias para divisor de voltaje

Para adaptar las señales de 5V a 3.3V del ESP32.

| Componente | Valor | Cantidad | Imagen |
|:-----------|:------|:---------|:-------|
| **Resistencia 1** | 10kΩ | 1 | ![10k](assets/R10k.jpg) |
| **Resistencia 2** | 5.1kΩ | 1 | ![5.1k](assets/R5k.png) |

**Fórmula del divisor de voltaje:**

```
V_out = V_in × (R2 / (R1 + R2))
```

Donde:
- V_in = 5V (salida del sensor)
- V_out = 3.3V (entrada segura para ESP32)
- R1 = 5.1kΩ
- R2 = 10kΩ

---

### Material de conexión

| Componente | Descripción | Cantidad |
|:-----------|:------------|:---------|
| **Protoboard** | Placa de pruebas 830 puntos | 1 |
| **Cables Dupont** | Macho-Macho, Macho-Hembra | Varios |

<div class="code-example" markdown="1">
**Protoboard**

![Protoboard](assets/PlacaPruebas.jpg)
</div>

<div class="code-example" markdown="1">
**Cables Dupont**

![Cables](assets/Dupont.jpg)
</div>

---

## 🧰 Software y plataformas

### Herramientas de desarrollo

| Software | Versión | Uso |
|:---------|:--------|:----|
| **Arduino IDE** | 2.0+ | Programación del ESP32 |
| **PlatformIO** | Opcional | IDE alternativo |
| **Git** | Última | Control de versiones |

### Plataformas IoT

| Plataforma | URL | Descripción |
|:-----------|:----|:------------|
| **Respira** | [calidadmedioambiental.org](http://calidadmedioambiental.org) | Plataforma de visualización |
| **Documentación Respira** | [Docs Respira](https://panstamp.github.io/respira_fiware/) | Guía de integración |

---

## 📦 Lista de compras

{: .note-title }
> Lista completa para replicar el proyecto

- [ ] 1x ESP32 Wemos Lolin32
- [ ] 1x Sensor MQ-135
- [ ] 1x Sensor Higrómetro
- [ ] 1x Resistencia 10kΩ
- [ ] 1x Resistencia 5.1kΩ
- [ ] 1x Protoboard 830 puntos
- [ ] 10x Cables Dupont macho-macho
- [ ] 5x Cables Dupont macho-hembra
- [ ] 1x Cable USB para programación

**Costo aproximado:** $30-50 USD (precios variables según región)

---

## 🔗 Enlaces útiles

- [Datasheet ESP32](https://www.espressif.com/en/products/socs/esp32)
- [Especificaciones MQ-135](https://www.winsen-sensor.com/sensors/voc-sensor/mq135.html)
- [Arduino ESP32 Core](https://github.com/espressif/arduino-esp32)

---

[Siguiente: Conexiones eléctricas →](conexiones){: .btn .btn-purple }