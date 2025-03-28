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

#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <Arduino.h>

/**
 * @class DebugLogger
 * @brief Classe pour gérer les messages de débogage sur un port série.
 * 
 * Cette classe permet d'afficher des messages de débogage sur un port série
 * avec des niveaux de débogage configurables. Chaque message peut être
 * précédé d'un préfixe indiquant le niveau de débogage.
 */
class DebugLogger {
public:
  enum DebugLevel {
    NONE,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
    BATTERY,
    I2C,
    INFLUXDB,
    TIME,
    WIFI,
    SD,
    SPIFF,
    WEB
  };

  struct DebugLevelInfo {
    String name;
    bool enabled;
  };

  /**
   * @brief Initialise le DebugLogger avec les niveaux de débogage spécifiés.
   * 
   * Configure le logger pour utiliser Serial par défaut avec un baudrate de 115200.
   * Permet de définir les niveaux de débogage activés.
   * 
   * @param levels Tableau contenant les niveaux de débogage activés et leurs noms.
   * @param numLevels Nombre de niveaux de débogage dans le tableau.
   */
  static void begin(const DebugLevelInfo levels[], size_t numLevels);

  /**
   * @brief Initialise le DebugLogger avec un port série et un baudrate personnalisés.
   * 
   * Configure le port série utilisé pour afficher les messages de débogage.
   * Permet également de définir les niveaux de débogage activés.
   * 
   * @param serialPort Port série utilisé pour le débogage (par exemple, Serial, Serial1, etc.).
   * @param baudrate Baudrate utilisé pour le port série (par exemple, 9600, 115200).
   * @param levels Tableau contenant les niveaux de débogage activés et leurs noms.
   * @param numLevels Nombre de niveaux de débogage dans le tableau.
   */
  static void begin(HardwareSerial* serialPort, unsigned long baudrate, const DebugLevelInfo levels[] = nullptr, size_t numLevels = 0);

  /**
   * @brief Définit ou modifie les niveaux de débogage actifs.
   * 
   * Permet de modifier dynamiquement les niveaux de débogage activés
   * pendant l'exécution du programme.
   * 
   * @param levels Tableau contenant les niveaux de débogage activés et leurs noms.
   * @param numLevels Nombre de niveaux de débogage dans le tableau.
   */
  static void setDebugLevel(const DebugLevelInfo levels[], size_t numLevels);

  /**
   * @brief Vérifie si un niveau de débogage spécifique est activé.
   * 
   * Permet de vérifier si un niveau de débogage est activé avant
   * d'afficher des messages ou d'exécuter du code conditionnel lié au débogage.
   * 
   * @param level Niveau de débogage à vérifier (depuis l'enum DebugLevel).
   * @return true si le niveau est activé, false sinon.
   */
  static bool isCategoryEnabled(DebugLevel level);

  /**
   * @brief Affiche un message de débogage sans retour à la ligne.
   * 
   * Affiche un message sur le port série configuré si le niveau
   * de débogage spécifié est activé. Le préfixe correspondant au niveau est ajouté
   * uniquement si le niveau change.
   * 
   * @param level Niveau de débogage pour le message (depuis l'enum DebugLevel).
   * @param message Message à afficher.
   */
  static void print(DebugLevel level, const String& message);

  /**
   * @brief Affiche un message de débogage avec un retour à la ligne.
   * 
   * Affiche un message sur le port série configuré si le niveau
   * de débogage spécifié est activé. Le préfixe correspondant au niveau est ajouté
   * uniquement si le niveau change. Après l'affichage, le niveau est réinitialisé.
   * 
   * @param level Niveau de débogage pour le message (depuis l'enum DebugLevel).
   * @param message Message à afficher.
   */
  static void println(DebugLevel level, const String& message);

  /**
   * @brief Active un niveau de débogage spécifique.
   * 
   * Permet d'activer dynamiquement un niveau de débogage
   * pendant l'exécution du programme.
   * 
   * @param level Niveau de débogage à activer (depuis l'enum DebugLevel).
   */
  static void enableCategory(DebugLevel level);

  /**
   * @brief Désactive un niveau de débogage spécifique.
   * 
   * Permet de désactiver dynamiquement un niveau de débogage
   * pendant l'exécution du programme.
   * 
   * @param level Niveau de débogage à désactiver (depuis l'enum DebugLevel).
   */
  static void disableCategory(DebugLevel level);

private:
  static DebugLevelInfo* debugLevels; /**< Tableau dynamique des niveaux de débogage activés */
  static size_t numLevels; /**< Nombre de niveaux de débogage */
  static HardwareSerial* serialPort; /**< Port série utilisé pour le débogage */
  static unsigned long baudrate; /**< Baudrate utilisé pour le port série */
  static DebugLevel lastLevel; /**< Dernier niveau de débogage utilisé */
};

#endif // DEBUG_LOGGER_H
