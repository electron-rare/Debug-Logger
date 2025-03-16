# 🔍 DebugLogger

![License](https://img.shields.io/badge/license-GPLv3-blue.svg)
![Version](https://img.shields.io/badge/version-1.0.0-brightgreen.svg)
![Platform](https://img.shields.io/badge/platform-Arduino-orange.svg)
![Status](https://img.shields.io/badge/status-stable-green.svg)

> Une bibliothèque Arduino légère et flexible pour gérer les messages de débogage avec différents niveaux de sévérité.

<div align="center">
  <img src="https://raw.githubusercontent.com/username/DebugLogger/main/docs/images/debug_console.png" alt="Capture d'écran de console de débogage" width="600"/>
</div>

## ✨ Fonctionnalités

- 🚦 **Niveaux de débogage personnalisables** : ERROR, WARNING, INFO, DEBUG et catégories spécifiques (BATTERY, I2C, etc.)
- 🎯 **Filtrage précis** : Affichez uniquement les messages des catégories qui vous intéressent
- 🔄 **Activation/désactivation dynamique** : Modifiez les niveaux de débogage pendant l'exécution
- 🔌 **Compatibilité étendue** : Fonctionne avec n'importe quel port série (Serial, Serial1, etc.)
- 🚀 **Facile à utiliser** : API simple et intuitive

## 📋 Table des matières

- [Installation](#-installation)
- [Utilisation rapide](#-utilisation-rapide)
- [Documentation](#-documentation)
- [Exemples](#-exemples)
- [Contribution](#-contribution)
- [Licence](#-licence)

## 📥 Installation

### Via le Gestionnaire de bibliothèques Arduino

1. Ouvrez l'IDE Arduino
2. Allez dans "Outils" > "Gérer les bibliothèques..."
3. Recherchez "DebugLogger"
4. Cliquez sur "Installer"

### Installation manuelle

```bash
# Clonez ce dépôt dans votre dossier de bibliothèques Arduino
git clone https://github.com/username/DebugLogger.git ~/Arduino/libraries/DebugLogger
```

## 🚀 Utilisation rapide

```cpp
#include <DebugLogger.h>

void setup() {
  // Définir les niveaux de débogage
  DebugLogger::DebugLevelInfo levels[] = {
    { "ERROR", true },
    { "WARNING", true },
    { "INFO", true },
    { "DEBUG", false }
  };
  
  // Initialiser le Logger
  DebugLogger::begin(levels, 4);
  
  DebugLogger::println(DebugLogger::INFO, "Système démarré");
}

void loop() {
  // Afficher des informations selon le niveau
  DebugLogger::println(DebugLogger::INFO, "Température: 24°C");
  
  // Vérifier si un niveau est activé avant d'effectuer des opérations
  if (DebugLogger::isCategoryEnabled(DebugLogger::DEBUG)) {
    // Code coûteux de débogage ici
  }
  
  delay(1000);
}
```

## 📚 Documentation

### Classes principales

- **DebugLogger** : Classe statique principale pour la gestion des messages de débogage

### Niveaux de débogage disponibles

```cpp
enum DebugLevel {
  NONE,     // Aucun message
  ERROR,    // Erreurs critiques
  WARNING,  // Avertissements
  INFO,     // Informations générales
  DEBUG,    // Informations détaillées
  BATTERY,  // Informations liées à la batterie
  I2C,      // Communication I2C
  INFLUXDB, // Interactions avec InfluxDB
  TIME,     // Informations temporelles
  WIFI,     // Communications WiFi
  SD,       // Opérations sur carte SD
  SPIFF,    // Opérations SPIFFS
  WEB       // Serveur web et communications
};
```

### Méthodes principales

| Méthode | Description |
|---------|-------------|
| `begin(levels[], size)` | Initialise le logger avec les niveaux spécifiés |
| `begin(serial, baudrate, levels[], size)` | Initialise avec port série personnalisé |
| `print(level, message)` | Affiche un message de débogage sans saut de ligne |
| `println(level, message)` | Affiche un message de débogage avec saut de ligne |
| `enableCategory(level)` | Active une catégorie de débogage |
| `disableCategory(level)` | Désactive une catégorie de débogage |
| `isCategoryEnabled(level)` | Vérifie si une catégorie est activée |

## 📝 Exemples

### Exemple basique

```cpp
#include <DebugLogger.h>

void setup() {
  DebugLogger::DebugLevelInfo levels[] = {
    { "ERROR", true },
    { "INFO", true }
  };
  
  DebugLogger::begin(levels, 2);
  DebugLogger::println(DebugLogger::INFO, "Initialisation terminée");
}

void loop() {
  static int counter = 0;
  counter++;
  
  if (counter % 10 == 0) {
    DebugLogger::println(DebugLogger::INFO, "Compteur: " + String(counter));
  }
  
  delay(1000);
}
```

Voir plus d'exemples dans le dossier [/examples](/examples)!

## 🤝 Contribution

Les contributions sont les bienvenues! N'hésitez pas à :

1. Fork ce dépôt
2. Créer une branche (`git checkout -b feature/amazing-feature`)
3. Commit vos changements (`git commit -m 'Add some amazing feature'`)
4. Push sur la branche (`git push origin feature/amazing-feature`)
5. Ouvrir une Pull Request

## 📄 Licence

Ce projet est sous licence GNU General Public License v3.0 - voir le fichier [LICENSE](LICENSE) pour plus de détails.