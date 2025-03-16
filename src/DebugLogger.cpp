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
 */

#include <DebugLogger.h>
#include <map> // map est utilisé pour les niveaux de débogage personnalisés

bool* DebugLogger::debugLevels = nullptr;
String* DebugLogger::debugLevelNames = nullptr;
size_t DebugLogger::numLevels = 0;
std::map<String, DebugLogger::DebugLevel> DebugLogger::customDebugLevels;

HardwareSerial* DebugLogger::serialPort = &Serial;
unsigned long DebugLogger::baudrate = 115200;

/**
 * @brief Initialise le DebugLogger avec les niveaux de débogage spécifiés.
 * 
 * @param levels Tableau de booléens représentant les niveaux de débogage activés.
 * @param numLevels Nombre de niveaux de débogage.
 */
void DebugLogger::begin(HardwareSerial* serialPort, unsigned long baudrate, const DebugLevel levels[], size_t numLevels) {
  DebugLogger::serialPort = serialPort;
  DebugLogger::baudrate = baudrate;
  DebugLogger::numLevels = numLevels;
  debugLevels = new bool[numLevels] {false};
  debugLevelNames = new String[numLevels] {"NONE", "ERROR", "WARNING", "INFO", "DEBUG"};
  delay(5000);
  serialPort->begin(baudrate);
  serialPort->println("DebugLogger initialisé");
  if (levels) {
    setDebugLevel(levels, numLevels);
  } else {
    setDefaultDebugLevels();
  }
  serialPort->println("Niveaux de débogage : ");
  
  for (size_t i = 0; i < numLevels; i++) {
    serialPort->print(debugLevelNames[i]);
    serialPort->print(" : ");
    serialPort->println(debugLevels[i] ? "Activé" : "Désactivé");
  }
  serialPort->println();
}

/**
 * @brief Définit les niveaux de débogage.
 * 
 * @param levels Tableau de booléens représentant les niveaux de débogage activés.
 * @param numLevels Nombre de niveaux de débogage.
 */
void DebugLogger::setDebugLevel(const DebugLevel levels[], size_t numLevels) {
  for (size_t i = 0; i < numLevels; i++) {
    debugLevels[i] = (levels[i] != NONE);
  }
}

/**
 * @brief Ajoute un nouveau niveau de débogage.
 * 
 * @param level Nom du nouveau niveau de débogage.
 */
void DebugLogger::addDebugLevel(const String& level) {
  DebugLevel newLevel = static_cast<DebugLevel>(numLevels + customDebugLevels.size());
  customDebugLevels[level] = newLevel;
  debugLevelNames = (String*)realloc(debugLevelNames, (numLevels + customDebugLevels.size()) * sizeof(String));
  debugLevelNames[newLevel] = level;
  debugLevels = (bool*)realloc(debugLevels, (numLevels + customDebugLevels.size()) * sizeof(bool));
  debugLevels[newLevel] = false;
}

/**
 * @brief Active ou désactive un niveau de débogage spécifique.
 * 
 * @param level Niveau de débogage.
 * @param enabled true pour activer, false pour désactiver.
 */
void DebugLogger::setDebugLevel(DebugLevel level, bool enabled) {
  debugLevels[level] = enabled;
}

/**
 * @brief Définit le nom d'un niveau de débogage.
 * 
 * @param level Niveau de débogage.
 * @param name Nom du niveau de débogage.
 */
void DebugLogger::setDebugLevelName(DebugLevel level, const String& name) {
  debugLevelNames[level] = name;
}

/**
 * @brief Vérifie si une catégorie de débogage est activée.
 * 
 * @param level Niveau de débogage à vérifier.
 * @return true si la catégorie est activée, false sinon.
 */
bool DebugLogger::isCategoryEnabled(DebugLevel level) {
  return debugLevels[level];
}

/**
 * @brief Affiche un message sans saut de ligne.
 * 
 * @param message Message à afficher.
 */
void DebugLogger::print(const String &message) {
  if (isCategoryEnabled(NONE)) {
    serialPort->print(message);
  }
}

/**
 * @brief Affiche un message avec un saut de ligne.
 * 
 * @param message Message à afficher.
 */
void DebugLogger::println(const String &message) {
  if (isCategoryEnabled(NONE)) {
    serialPort->println(message);
  }
}

/**
 * @brief Affiche un message avec un préfixe sans saut de ligne.
 * 
 * @param level Niveau de débogage.
 * @param prefix Préfixe à afficher.
 * @param message Message à afficher.
 */
void DebugLogger::printWithPrefix(DebugLevel level, const String &prefix, const String &message) {
  if (isCategoryEnabled(level)) {
    static bool firstPrint = true;
    if (firstPrint) {
      serialPort->print(prefix);
      firstPrint = false;
    }
    serialPort->print(message);
  }
}

/**
 * @brief Affiche un message avec un préfixe et un saut de ligne.
 * 
 * @param level Niveau de débogage.
 * @param prefix Préfixe à afficher.
 * @param message Message à afficher.
 */
void DebugLogger::printlnWithPrefix(DebugLevel level, const String &prefix, const String &message) {
  if (isCategoryEnabled(level)) {
    static bool firstPrint = true;
    if (firstPrint) {
      serialPort->print(prefix);
    }
    serialPort->println(message);
    firstPrint = true;
  }
}

/**
 * @brief Affiche un message de débogage avec un préfixe correspondant au niveau.
 * 
 * @param level Niveau de débogage.
 * @param message Message à afficher.
 */
void DebugLogger::printDebug(DebugLevel level, const String &message) {
  printWithPrefix(level, String(debugLevelNames[level]) + " : ", message);
}

/**
 * @brief Affiche un message de débogage avec un préfixe et un saut de ligne.
 * 
 * @param level Niveau de débogage.
 * @param message Message à afficher.
 */
void DebugLogger::printlnDebug(DebugLevel level, const String &message) {
  printlnWithPrefix(level, String(debugLevelNames[level]) + " : ", message);
}

/**
 * @brief Définit les niveaux de débogage par défaut.
 */
void DebugLogger::setDefaultDebugLevels() {
  bool defaultLevels[] = {false, true, true, true, false};
  setDebugLevel(defaultLevels, 5);
}
