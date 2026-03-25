# 🤖 Système de Navigation Autonome (AVR Multi-Robots)

Un système embarqué de bout en bout impliquant la coordination de deux robots distincts via communication infrarouge pour la cartographie et la navigation d'un parcours d'obstacles.

## 🎯 Vue d'ensemble
Ce projet démontre la conception d'une architecture logicielle robuste en C++ *bare-metal* sur microcontrôleur ATMega324PA. Le système fonctionne de manière totalement déterministe et autonome, sans système d'exploitation (RTOS), en s'appuyant sur une machine à états finis et la gestion matérielle des interruptions.

## 🛠️ Stack Technologique & Matériel
* **Microcontrôleur :** ATMega324PA (AVR)
* **Langage :** C/C++ (Bare-Metal, manipulation directe des registres)
* **Capteurs :** * Suivi de ligne : Cytron Maker Line (Algorithme PID)
  * Distance : Sharp GP2Y0A21YK0F (ADC, filtrage)
* **Communication :** Infrarouge (PWM Hardware 38kHz, Démodulation)

## 📂 Structure de l'Architecture

L'architecture est divisée en modules pour séparer l'abstraction matérielle de la logique applicative :

```bash
.
├── 📚 lib/          # Pilotes matériels (Timers, ADC, PWM, UART) et services partagés
├── 🤖 app1/         # Logique Robot 1 : Centrage, Machine à états de réception IR
└── 🤖 app2/         # Logique Robot 2 : PID de navigation, Cartographie, Transmission IR
