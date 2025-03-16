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

DebugLogger::DebugLevelInfo* DebugLogger::debugLevels = nullptr;
size_t DebugLogger::numLevels = 0;

HardwareSerial* DebugLogger::serialPort = &Serial;
unsigned long DebugLogger::baudrate = 115200;

/**
 * @brief Initialise le DebugLogger avec un port série et baudrate personnalisés.
 * 
 * Cette méthode permet de spécifier un port série spécifique pour la sortie de débogage
 * ainsi qu'un baudrate personnalisé. Les niveaux de débogage sont optionnels.
 * 
 * @param serialPort Port série utilisé pour le débogage (HardwareSerial, comme Serial, Serial1, etc.).
 * @param baudrate Baudrate utilisé pour le port série (par exemple 9600, 115200).
 * @param levels Tableau de structures représentant les niveaux de débogage activés et leurs noms (optionnel).
 * @param numLevels Nombre de niveaux de débogage dans le tableau (optionnel).
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

  delay(5000);
  DebugLogger::serialPort->begin(DebugLogger::baudrate);
  DebugLogger::serialPort->println("DebugLogger initialisé");
  DebugLogger::serialPort->println("Niveaux de débogage : ");
  
  for (size_t i = 0; i < DebugLogger::numLevels; i++) {
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
 * @param levels Tableau de structures représentant les niveaux de débogage activés et leurs noms.
 * @param numLevels Nombre de niveaux de débogage dans le tableau.
 */
void DebugLogger::begin(const DebugLevelInfo levels[], size_t numLevels) {
  begin(&Serial, 115200, levels, numLevels);
}

/**
 * @brief Définit ou modifie les niveaux de débogage actifs.
 * 
 * Cette méthode permet de modifier les niveaux de débogage pendant l'exécution
 * du programme sans avoir à réinitialiser le logger complet.
 * 
 * @param levels Tableau de structures représentant les niveaux de débogage activés et leurs noms.
 * @param numLevels Nombre de niveaux de débogage dans le tableau.
 */
void DebugLogger::setDebugLevel(const DebugLevelInfo levels[], size_t numLevels) {
  for (size_t i = 0; i < numLevels; i++) {
    debugLevels[i].enabled = levels[i].enabled;
    debugLevels[i].name = levels[i].name;
  }
}

/**
 * @brief Vérifie si une catégorie de débogage spécifique est activée.
 * 
 * Utilisez cette méthode pour vérifier si un niveau de débogage est actif avant
 * d'exécuter du code conditionnel lié au débogage.
 * 
 * @param level Niveau de débogage à vérifier (depuis l'enum DebugLevel).
 * @return true si la catégorie est activée et que les logs de ce niveau seront affichés, false sinon.
 */
bool DebugLogger::isCategoryEnabled(DebugLevel level) {
  return debugLevels[level].enabled;
}

/**
 * @brief Affiche un message de débogage avec un préfixe correspondant au niveau.
 * 
 * Cette méthode affiche un message sur le port série configuré si la catégorie
 * de débogage spécifiée est activée. Le message n'inclut pas de retour à la ligne.
 * 
 * @param level Niveau de débogage pour le message (depuis l'enum DebugLevel).
 * @param message Message à afficher.
 */
void DebugLogger::print(DebugLevel level, const String& message) {
  if (isCategoryEnabled(level)) {
    serialPort->print(String(debugLevels[level].name) + " : " + message);
  }
}

/**
 * @brief Affiche un message de débogage avec un préfixe et un saut de ligne.
 * 
 * Cette méthode affiche un message sur le port série configuré si la catégorie
 * de débogage spécifiée est activée, suivi d'un retour à la ligne.
 * 
 * @param level Niveau de débogage pour le message (depuis l'enum DebugLevel).
 * @param message Message à afficher.
 */
void DebugLogger::println(DebugLevel level, const String& message) {
  if (isCategoryEnabled(level)) {
    serialPort->println(String(debugLevels[level].name) + " : " + message);
  }
}

/**
 * @brief Active une catégorie de débogage spécifique.
 * 
 * Utilisez cette méthode pour activer dynamiquement un niveau de débogage
 * pendant l'exécution du programme.
 * 
 * @param level Niveau de débogage à activer (depuis l'enum DebugLevel).
 */
void DebugLogger::enableCategory(DebugLevel level) {
  debugLevels[level].enabled = true;
}

/**
 * @brief Désactive une catégorie de débogage spécifique.
 * 
 * Utilisez cette méthode pour désactiver dynamiquement un niveau de débogage
 * pendant l'exécution du programme.
 * 
 * @param level Niveau de débogage à désactiver (depuis l'enum DebugLevel).
 */
void DebugLogger::disableCategory(DebugLevel level) {
  debugLevels[level].enabled = false;
}
