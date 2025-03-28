/*
 * This file is part of DebugLogger.
 *
 * DebugLogger is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DebugLogger is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DebugLogger. If not, see <http://www.gnu.org/licenses/>.
 *
 * Created by Clément Saillant, 2025.
 * https://github.com/electron-rare/Debug-Logger
 */

#include <DebugLogger.h>

DebugLogger::DebugLevelInfo* DebugLogger::debugLevels = nullptr;
size_t DebugLogger::numLevels = 0;

HardwareSerial* DebugLogger::serialPort = &Serial;
unsigned long DebugLogger::baudrate = 115200;

DebugLogger::DebugLevel DebugLogger::lastLevel = DebugLogger::NONE; 

/**
 * @brief Initialise le DebugLogger avec un port série et un baudrate personnalisés.
 * 
 * Cette méthode configure le port série utilisé pour afficher les messages de débogage.
 * Elle permet également de définir les niveaux de débogage activés et leurs noms.
 * 
 * @param serialPort Port série utilisé pour le débogage (par exemple, Serial, Serial1, etc.).
 * @param baudrate Baudrate utilisé pour le port série (par exemple, 9600, 115200).
 * @param levels Tableau contenant les niveaux de débogage activés et leurs noms.
 * @param numLevels Nombre de niveaux de débogage dans le tableau.
 */
void DebugLogger::begin(HardwareSerial* serialPort, unsigned long baudrate, const DebugLevelInfo levels[], size_t numLevels) {
  DebugLogger::serialPort = serialPort ? serialPort : &Serial;
  DebugLogger::baudrate = baudrate ? baudrate : 115200;
  DebugLogger::numLevels = numLevels;

  if (levels) {
    debugLevels = new DebugLevelInfo[numLevels];
    for (size_t i = 0; i < numLevels; ++i) {
      debugLevels[i].name = levels[i].name;
      debugLevels[i].enabled = levels[i].enabled;
    }
  }
  DebugLogger::serialPort->begin(DebugLogger::baudrate); v
  DebugLogger::serialPort->println("DebugLogger initialisé");
  DebugLogger::serialPort->println("Niveaux de débogage : ");
  
  for (size_t i = 0; i < DebugLogger::numLevels; i++) { // Boucle pour afficher les niveaux de débogage
    DebugLogger::serialPort->print("Niveau ");
    DebugLogger::serialPort->print(debugLevels[i].name);
    DebugLogger::serialPort->print(" : ");
    DebugLogger::serialPort->println(debugLevels[i].enabled ? "Activé" : "Désactivé");
  }
  DebugLogger::serialPort->println();
}

/**
 * @brief Initialise le DebugLogger avec les niveaux de débogage spécifiés.
 * 
 * Cette méthode configure le logger pour utiliser Serial par défaut avec un baudrate de 115200.
 * Elle permet de définir les niveaux de débogage qui seront activés dans l'application.
 * 
 * @param levels Tableau contenant les niveaux de débogage activés et leurs noms.
 * @param numLevels Nombre de niveaux de débogage dans le tableau.
 */
void DebugLogger::begin(const DebugLevelInfo levels[], size_t numLevels) {
  begin(&Serial, 115200, levels, numLevels);
}

/**
 * @brief Définit ou modifie les niveaux de débogage actifs.
 * 
 * Cette méthode permet de modifier dynamiquement les niveaux de débogage activés
 * pendant l'exécution du programme.
 * 
 * @param levels Tableau contenant les niveaux de débogage activés et leurs noms.
 * @param numLevels Nombre de niveaux de débogage dans le tableau.
 */
void DebugLogger::setDebugLevel(const DebugLevelInfo levels[], size_t numLevels) {
  for (size_t i = 0; i < numLevels; i++) {
    debugLevels[i].enabled = levels[i].enabled;
    debugLevels[i].name = levels[i].name;
  }
}

/**
 * @brief Vérifie si un niveau de débogage spécifique est activé.
 * 
 * Cette méthode permet de vérifier si un niveau de débogage est activé avant
 * d'afficher des messages ou d'exécuter du code conditionnel lié au débogage.
 * 
 * @param level Niveau de débogage à vérifier (depuis l'enum DebugLevel).
 * @return true si le niveau est activé, false sinon.
 */
bool DebugLogger::isCategoryEnabled(DebugLevel level) {
  return debugLevels[level].enabled;
}

/**
 * @brief Affiche un message de débogage sans retour à la ligne.
 * 
 * Cette méthode affiche un message sur le port série configuré si le niveau
 * de débogage spécifié est activé. Le préfixe correspondant au niveau est ajouté
 * uniquement si le niveau change.
 * 
 * @param level Niveau de débogage pour le message (depuis l'enum DebugLevel).
 * @param message Message à afficher.
 */
void DebugLogger::print(DebugLevel level, const String& message) {
  if (isCategoryEnabled(level)) { // Vérifier si le niveau est activé
    if (level != lastLevel) {    // Vérifier si le niveau a changé
      serialPort->print(String(debugLevels[level].name) + " : "); // Afficher le préfixe si le niveau a changé
      lastLevel = level; // Mettre à jour le dernier niveau
    }
    serialPort->print(message); // Afficher le message sans retour à la ligne
  }
}

/**
 * @brief Affiche un message de débogage avec un retour à la ligne.
 * 
 * Cette méthode affiche un message sur le port série configuré si le niveau
 * de débogage spécifié est activé. Le préfixe correspondant au niveau est ajouté
 * uniquement si le niveau change. Après l'affichage, le niveau est réinitialisé.
 * 
 * @param level Niveau de débogage pour le message (depuis l'enum DebugLevel).
 * @param message Message à afficher.
 */
void DebugLogger::println(DebugLevel level, const String& message) {
  if (isCategoryEnabled(level)) {
    if (level != lastLevel) { // Vérifier si le niveau a changé
      serialPort->print(String(debugLevels[level].name) + " : "); // Afficher le préfixe si le niveau a changé
      lastLevel = level; // Mettre à jour le dernier niveau
    }
    serialPort->println(message); // Afficher le message avec un retour à la ligne
    lastLevel = DebugLevel::NONE; // Réinitialiser le niveau après l'impression
  }
}

/**
 * @brief Active un niveau de débogage spécifique.
 * 
 * Cette méthode permet d'activer dynamiquement un niveau de débogage
 * pendant l'exécution du programme.
 * 
 * @param level Niveau de débogage à activer (depuis l'enum DebugLevel).
 */
void DebugLogger::enableCategory(DebugLevel level) {
  debugLevels[level].enabled = true;
}

/**
 * @brief Désactive un niveau de débogage spécifique.
 * 
 * Cette méthode permet de désactiver dynamiquement un niveau de débogage
 * pendant l'exécution du programme.
 * 
 * @param level Niveau de débogage à désactiver (depuis l'enum DebugLevel).
 */
void DebugLogger::disableCategory(DebugLevel level) {
  debugLevels[level].enabled = false;
}
