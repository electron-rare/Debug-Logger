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

#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <Arduino.h>
#include <map> // map est utilisé pour les niveaux de débogage personnalisés

/**
 * @class DebugLogger
 * @brief Classe pour gérer les messages de débogage sur une carte programmé avec le langage Arduino.
 */
class DebugLogger {
public:
  /**
   * @enum DebugLevel
   * @brief Niveaux de débogage disponibles.
   */
  enum DebugLevel {
    NONE,      /**< Aucun débogage */
    ERROR,     /**< Débogage des erreurs */
    WARNING,   /**< Débogage des avertissements */
    INFO,      /**< Débogage des informations */
    DEBUG,     /**< Débogage général */
    CUSTOM     /**< Débogage personnalisé */
  };

  /**
   * @brief Initialise le DebugLogger avec les niveaux de débogage spécifiés.
   * @param levels Tableau de booléens représentant les niveaux de débogage activés.
   * @param numLevels Nombre de niveaux de débogage.
   */
  static void begin(const bool levels[], size_t numLevels);

  /**
   * @brief Initialise le DebugLogger avec le port série, le baudrate et les niveaux de débogage spécifiés.
   * @param serialPort Port série utilisé pour le débogage.
   * @param baudrate Baudrate utilisé pour le port série.
   * @param levels Tableau de booléens représentant les niveaux de débogage activés.
   * @param numLevels Nombre de niveaux de débogage.
   */
  static void begin(HardwareSerial* serialPort, unsigned long baudrate, const bool levels[] = nullptr, size_t numLevels = 0);

  /**
   * @brief Initialise le DebugLogger avec le port série, le baudrate et les niveaux de débogage spécifiés.
   * @param serialPort Port série utilisé pour le débogage.
   * @param baudrate Baudrate utilisé pour le port série.
   * @param levels Vecteur de booléens représentant les niveaux de débogage activés.
   */
  static void begin(HardwareSerial* serialPort, unsigned long baudrate, const std::vector<bool>& levels);

  /**
   * @brief Initialise le DebugLogger avec le port série, le baudrate et les niveaux de débogage spécifiés.
   * @param serialPort Port série utilisé pour le débogage.
   * @param baudrate Baudrate utilisé pour le port série.
   * @param levels Tableau dynamique de booléens représentant les niveaux de débogage activés.
   * @param numLevels Nombre de niveaux de débogage.
   */
  static void begin(HardwareSerial* serialPort, unsigned long baudrate, const bool* levels, size_t numLevels);

  /**
   * @brief Initialise le DebugLogger avec le port série, le baudrate et les niveaux de débogage spécifiés.
   * @param serialPort Port série utilisé pour le débogage.
   * @param baudrate Baudrate utilisé pour le port série.
   * @param levels Tableau de niveaux de débogage représentant les niveaux de débogage activés.
   * @param numLevels Nombre de niveaux de débogage.
   */
  static void begin(HardwareSerial* serialPort, unsigned long baudrate, const DebugLevel levels[] = nullptr, size_t numLevels = 0);

  /**
   * @brief Définit les niveaux de débogage.
   * @param levels Tableau de booléens représentant les niveaux de débogage activés.
   * @param numLevels Nombre de niveaux de débogage.
   */
  static void setDebugLevel(const bool levels[], size_t numLevels);

  /**
   * @brief Définit les niveaux de débogage.
   * @param levels Vecteur de booléens représentant les niveaux de débogage activés.
   */
  static void setDebugLevel(const std::vector<bool>& levels);

  /**
   * @brief Définit les niveaux de débogage.
   * @param levels Tableau dynamique de booléens représentant les niveaux de débogage activés.
   * @param numLevels Nombre de niveaux de débogage.
   */
  static void setDebugLevel(const bool* levels, size_t numLevels);

  /**
   * @brief Définit les niveaux de débogage.
   * @param levels Tableau de niveaux de débogage représentant les niveaux de débogage activés.
   * @param numLevels Nombre de niveaux de débogage.
   */
  static void setDebugLevel(const DebugLevel levels[], size_t numLevels);

  /**
   * @brief Ajoute un nouveau niveau de débogage.
   * @param level Nom du nouveau niveau de débogage.
   */
  static void addDebugLevel(const String& level);

  /**
   * @brief Vérifie si une catégorie de débogage est activée.
   * @param level Niveau de débogage à vérifier.
   * @return true si la catégorie est activée, false sinon.
   */
  static bool isCategoryEnabled(DebugLevel level);

  /**
   * @brief Affiche un message sans saut de ligne.
   * @param message Message à afficher.
   */
  static void print(const String &message);

  /**
   * @brief Affiche un message avec un saut de ligne.
   * @param message Message à afficher.
   */
  static void println(const String &message);

  /**
   * @brief Affiche un message de débogage avec un préfixe correspondant au niveau.
   * @param level Niveau de débogage.
   * @param message Message à afficher.
   */
  static void printDebug(DebugLevel level, const String &message);

  /**
   * @brief Affiche un message de débogage avec un préfixe et un saut de ligne.
   * @param level Niveau de débogage.
   * @param message Message à afficher.
   */
  static void printlnDebug(DebugLevel level, const String &message);

  /**
   * @brief Active ou désactive un niveau de débogage spécifique.
   * @param level Niveau de débogage.
   * @param enabled true pour activer, false pour désactiver.
   */
  static void setDebugLevel(DebugLevel level, bool enabled);

  /**
   * @brief Définit le nom d'un niveau de débogage.
   * @param level Niveau de débogage.
   * @param name Nom du niveau de débogage.
   */
  static void setDebugLevelName(DebugLevel level, const String& name);

  /**
   * @brief Définit les niveaux de débogage par défaut.
   */
  static void setDefaultDebugLevels();

private:
  static bool* debugLevels; /**< Tableau dynamique des niveaux de débogage activés */
  static String* debugLevelNames; /**< Tableau dynamique des noms des niveaux de débogage */
  static size_t numLevels; /**< Nombre de niveaux de débogage */
  static std::map<String, DebugLevel> customDebugLevels; /**< Map des niveaux de débogage personnalisés */
  static HardwareSerial* serialPort; /**< Port série utilisé pour le débogage */
  static unsigned long baudrate; /**< Baudrate utilisé pour le port série */

  /**
   * @brief Affiche un message avec un préfixe sans saut de ligne.
   * @param level Niveau de débogage.
   * @param prefix Préfixe à afficher.
   * @param message Message à afficher.
   */
  static void printWithPrefix(DebugLevel level, const String &prefix, const String &message);

  /**
   * @brief Affiche un message avec un préfixe et un saut de ligne.
   * @param level Niveau de débogage.
   * @param prefix Préfixe à afficher.
   * @param message Message à afficher.
   */
  static void printlnWithPrefix(DebugLevel level, const String &prefix, const String &message);
};

#endif // DEBUG_LOGGER_H
