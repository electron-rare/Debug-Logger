# DebugLogger

`DebugLogger` est une classe pour gérer les messages de débogage sur une carte Arduino. Utilisez cette bibliothèque pour faciliter le débogage de vos projets Arduino.

![License](https://img.shields.io/badge/license-GPLv3-blue.svg)
![Version](https://img.shields.io/badge/version-1.0.0-brightgreen.svg)

## Utilité et Avantages

La librairie `DebugLogger` offre plusieurs avantages pour le développement de projets Arduino :

- **Facilité de Débogage** : Simplifie l'affichage des messages de débogage, ce qui permet de suivre facilement le flux d'exécution et d'identifier les problèmes.
- **Niveaux de Débogage** : Permet de définir différents niveaux de débogage (INFO, DEBUG, ERROR, etc.) pour filtrer les messages en fonction de leur importance.
- **Personnalisation** : Les utilisateurs peuvent définir des noms personnalisés pour les niveaux de débogage et configurer les niveaux activés ou désactivés.
- **Affichage Structuré** : Les méthodes avec préfixe permettent d'afficher des messages de manière structurée, facilitant ainsi la lecture des logs.
- **Flexibilité** : Compatible avec différentes configurations de projets Arduino et peut être facilement intégré dans des projets existants.

### Utilité des Niveaux de Débogage

Définir des niveaux de débogage est essentiel pour plusieurs raisons :

- **Filtrage des Messages** : Permet de contrôler la quantité d'informations affichées en fonction de l'importance des messages. Par exemple, en mode production, vous pouvez choisir de n'afficher que les erreurs critiques.
- **Organisation** : Aide à organiser les messages de débogage en catégories, ce qui facilite la recherche et l'analyse des logs.
- **Performance** : Réduit la surcharge en évitant l'affichage de messages de débogage non essentiels, améliorant ainsi les performances du système.
- **Clarté** : Améliore la lisibilité des logs en séparant les messages d'information, de débogage et d'erreur.

### Définir le Baudrate et le Port Série

Pour plus de compatibilité, vous pouvez définir le baudrate et le port série utilisés par `DebugLogger`. Voici comment procéder :

```cpp
#include <DebugLogger.h>

DebugLogger logger;

void setup() {
  Serial.begin(9600); // Définir le baudrate
  logger.begin(&Serial); // Définir le port série
  logger.setDefaultDebugLevels();
}
```

Vous pouvez remplacer `9600` par le baudrate de votre choix et `&Serial` par le port série que vous utilisez (par exemple, `&Serial1`).

## Licence

```plaintext
This file is part of DebugLogger.

DebugLogger is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DebugLogger is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with DebugLogger. If not, see <http://www.gnu.org/licenses/>.

Created by Clément Saillant, 2025.
```

## Utilisation

### Initialisation

Pour initialiser le `DebugLogger` avec les niveaux de débogage par défaut :

```cpp
#include <DebugLogger.h>

DebugLogger logger;

void setup() {
  Serial.begin(9600); // Définir le baudrate
  logger.begin(&Serial); // Définir le port série
  logger.setDefaultDebugLevels();
}
```

### Méthodes

- `print(const String &message)`: Affiche un message sans saut de ligne.
- `println(const String &message)`: Affiche un message avec un saut de ligne.
- `printDebug(DebugLevel level, const String &message)`: Affiche un message de débogage avec un préfixe correspondant au niveau.
- `printlnDebug(DebugLevel level, const String &message)`: Affiche un message de débogage avec un préfixe et un saut de ligne.
- `setDebugLevel(DebugLevel level, bool enabled)`: Active ou désactive un niveau de débogage spécifique.
- `setDebugLevelName(DebugLevel level, const char* name)`: Définit le nom d'un niveau de débogage.
- `setDefaultDebugLevels()`: Définit les niveaux de débogage par défaut.

### Exemples

#### Exemple d'initialisation et d'utilisation de base

```cpp
#include <DebugLogger.h>

DebugLogger logger;

void setup() {
  Serial.begin(9600); // Définir le baudrate
  logger.begin(&Serial); // Définir le port série
  logger.setDefaultDebugLevels();

  logger.setDebugLevelName(DebugLogger::ERROR, "ERREUR");
  logger.setDebugLevelName(DebugLogger::INFO, "INFORMATION");

  logger.println("Ceci est un message de log.");
  logger.printlnDebug(DebugLogger::INFO, "Ceci est un message d'information.");
  logger.printlnDebug(DebugLogger::ERROR, "Ceci est un message d'erreur.");
}

void loop() {
  // Code principal
}
```

#### Exemple de configuration et d'utilisation des niveaux de débogage spécifiques

```cpp
#include <DebugLogger.h>

DebugLogger logger;

void setup() {
  Serial.begin(9600); // Définir le baudrate
  logger.begin(&Serial); // Définir le port série
  DebugLogger::DebugLevel levels[NUM_LEVELS] = {DebugLogger::NONE, DebugLogger::ERROR, DebugLogger::WARNING, DebugLogger::NONE, DebugLogger::DEBUG};
  logger.begin(levels);

  bool isEnabled = logger.isCategoryEnabled(DebugLogger::DEBUG);
  Serial.print("DEBUG level is ");
  Serial.println(isEnabled ? "enabled" : "disabled");

  logger.printDebug(DebugLogger::DEBUG, "Ceci est un message de débogage.");
  logger.printlnDebug(DebugLogger::DEBUG, "Ceci est un message de débogage avec saut de ligne.");
}

void loop() {
  // Code principal
}
```

#### Exemple d'utilisation des méthodes avec préfixe personnalisé

```cpp
#include <DebugLogger.h>

DebugLogger logger;

void setup() {
  Serial.begin(9600); // Définir le baudrate
  logger.begin(&Serial); // Définir le port série
  logger.setDefaultDebugLevels();

  logger.printWithPrefix(DebugLogger::INFO, "INFO: ", "Ceci est un message d'information.");
  logger.printlnWithPrefix(DebugLogger::INFO, "INFO: ", "Ceci est un message d'information avec saut de ligne.");
}

void loop() {
  // Code principal
}
```

## Mots-clés

Arduino, Debug, Logger, Serial, Débogage, Messages, Niveaux de débogage, Préfixe, Informations, Erreurs, Avertissements, Bibliothèque Arduino, Clément Saillant
