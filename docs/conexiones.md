# 🔌 Conexiones del sistema

## Diagrama general
## 🔌 Diagrama de conexiones (Mermaid)

<div class="mermaid">
graph TD
    %% ==== SENSOR MQ-135 ====
    subgraph Sensor_MQ135
        VCC5V[+5V del sensor MQ135]
        AO[Salida AO MQ135]
        GND_MQ[GND MQ135]
    end

    %% ==== SENSOR HIGRÓMETRO ====
    subgraph Sensor_Higrometro
        VCC_HIGRO[+5V del higrómetro]
        AO_HIGRO[Salida AO higrómetro]
        GND_HIGRO[GND higrómetro]
    end

    %% ==== DIVISORES ====
    subgraph Divisor_MQ135
        R1_MQ[Resistencia R1 5.1kΩ]
        R2_MQ[Resistencia R2 10kΩ]
    end

    subgraph Divisor_Higrometro
        R1_H[Resistencia R1 5.1kΩ]
        R2_H[Resistencia R2 10kΩ]
    end

    %% ==== ESP32 ====
    subgraph ESP32_WEMOS_LOLIN32
        VCC_ESP[5V de la ESP32]
        ADC_MQ[Pin ADC GPIO34 MQ135]
        ADC_H[Pin ADC GPIO35 Higrometro]
        GND_ESP[GND ESP32]
    end

    %% ==== CONEXIONES MQ-135 ====
    VCC_ESP -->|Alimenta sensor MQ135| VCC5V
    AO --> R1_MQ
    R1_MQ -->|Punto medio MQ135| ADC_MQ
    R1_MQ --> R2_MQ
    R2_MQ --> GND_MQ

    %% ==== CONEXIONES HIGRÓMETRO ====
    VCC_ESP -->|Alimenta sensor Higrometro| VCC_HIGRO
    AO_HIGRO --> R1_H
    R1_H -->|Punto medio Higrometro| ADC_H
    R1_H --> R2_H
    R2_H --> GND_HIGRO

    %% ==== GND COMÚN ====
    GND_MQ --- GND_HIGRO --- GND_ESP
</div>

<script type="module">
  import mermaid from "https://cdn.jsdelivr.net/npm/mermaid@11/dist/mermaid.esm.min.mjs";
  mermaid.initialize({ startOnLoad: true, theme: "default" });
</script>

## Montaje
![Thinkercad](assets/Tinkercad.png)

## Protoboard
![Montaje](assets/Protoboard.jpg)

![Montaje](assets/Protoboard_1.jpg)

![Montaje](assets/Protoboard_2.jpg)

![Montaje](assets/Protoboard_3.jpg)