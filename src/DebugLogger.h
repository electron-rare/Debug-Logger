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

/**
 * @class DebugLogger
 * @brief Classe pour gérer les messages de débogage sur une carte programmé avec le langage Arduino.
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
   * Cette méthode configure le logger pour utiliser Serial par défaut avec un baudrate de 115200.
   * Elle permet de définir les niveaux de débogage qui seront activés dans l'application.
   * 
   * @param levels Tableau de structures représentant les niveaux de débogage activés et leurs noms.
   * @param numLevels Nombre de niveaux de débogage dans le tableau.
   */
  static void begin(const DebugLevelInfo levels[], size_t numLevels);

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
  static void begin(HardwareSerial* serialPort, unsigned long baudrate, const DebugLevelInfo levels[] = nullptr, size_t numLevels = 0);

  /**
   * @brief Définit ou modifie les niveaux de débogage actifs.
   * 
   * Cette méthode permet de modifier les niveaux de débogage pendant l'exécution
   * du programme sans avoir à réinitialiser le logger complet.
   * 
   * @param levels Tableau de structures représentant les niveaux de débogage activés et leurs noms.
   * @param numLevels Nombre de niveaux de débogage dans le tableau.
   */
  static void setDebugLevel(const DebugLevelInfo levels[], size_t numLevels);

  /**
   * @brief Vérifie si une catégorie de débogage spécifique est activée.
   * 
   * Utilisez cette méthode pour vérifier si un niveau de débogage est actif avant
   * d'exécuter du code conditionnel lié au débogage.
   * 
   * @param level Niveau de débogage à vérifier (depuis l'enum DebugLevel).
   * @return true si la catégorie est activée et que les logs de ce niveau seront affichés, false sinon.
   */
  static bool isCategoryEnabled(DebugLevel level);

  /**
   * @brief Affiche un message de débogage avec un préfixe correspondant au niveau.
   * 
   * Cette méthode affiche un message sur le port série configuré si la catégorie
   * de débogage spécifiée est activée. Le message n'inclut pas de retour à la ligne.
   * 
   * @param level Niveau de débogage pour le message (depuis l'enum DebugLevel).
   * @param message Message à afficher.
   */
  static void print(DebugLevel level, const String& message);

  /**
   * @brief Affiche un message de débogage avec un préfixe et un saut de ligne.
   * 
   * Cette méthode affiche un message sur le port série configuré si la catégorie
   * de débogage spécifiée est activée, suivi d'un retour à la ligne.
   * 
   * @param level Niveau de débogage pour le message (depuis l'enum DebugLevel).
   * @param message Message à afficher.
   */
  static void println(DebugLevel level, const String& message);

  /**
   * @brief Active une catégorie de débogage spécifique.
   * 
   * Utilisez cette méthode pour activer dynamiquement un niveau de débogage
   * pendant l'exécution du programme.
   * 
   * @param level Niveau de débogage à activer (depuis l'enum DebugLevel).
   */
  static void enableCategory(DebugLevel level);

  /**
   * @brief Désactive une catégorie de débogage spécifique.
   * 
   * Utilisez cette méthode pour désactiver dynamiquement un niveau de débogage
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
};

#endif // DEBUG_LOGGER_H
