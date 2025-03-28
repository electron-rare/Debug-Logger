/*
 * Exemple avancé d'utilisation de la bibliothèque DebugLogger
 * 
 * Cet exemple montre des utilisations plus sophistiquées de la bibliothèque DebugLogger,
 * y compris la modification dynamique des niveaux de débogage et l'utilisation
 * de différents ports série.
 * 
 * Note: Cet exemple est conçu pour un ESP32 qui possède plusieurs ports série.
 * Adaptez-le à votre matériel si nécessaire.
 * 
 * Créé par Clément Saillant, 2025.
 */

#include <DebugLogger.h>

// Structure pour simuler des données de batterie
struct BatteryData {
  float voltage;
  float current;
  float temperature;
  int percentage;
};

// Variables globales
BatteryData battery = {12.6, 0.5, 25.2, 85};
unsigned long lastSampleTime = 0;
const int samplingInterval = 2000;  // 2 secondes
bool systemError = false;

// Fonction pour simuler l'acquisition de données
void sampleBatteryData() {
  // Simuler des variations de données
  battery.voltage = 11.8 + (random(0, 100) / 100.0);
  battery.current = -0.5 + (random(0, 100) / 100.0);
  battery.temperature = 20.0 + (random(0, 100) / 10.0);
  battery.percentage = 60 + random(0, 30);
  
  // Simuler occasionnellement un problème
  if (random(0, 100) < 5) {  // 5% de chances d'erreur
    battery.voltage = 9.2;  // Tension anormalement basse
    systemError = true;
  } else {
    systemError = false;
  }
}

// Fonction qui enregistre les données de batterie
void logBatteryStatus() {
  DebugLogger::println(DebugLogger::BATTERY, "--- Statut Batterie ---");
  DebugLogger::println(DebugLogger::BATTERY, "Tension: " + String(battery.voltage) + " V");
  DebugLogger::println(DebugLogger::BATTERY, "Courant: " + String(battery.current) + " A");
  DebugLogger::println(DebugLogger::BATTERY, "Température: " + String(battery.temperature) + " °C");
  DebugLogger::println(DebugLogger::BATTERY, "Niveau de charge: " + String(battery.percentage) + " %");
}

// Fonction pour vérifier les erreurs
void checkForErrors() {
  if (battery.voltage < 10.0) {
    DebugLogger::println(DebugLogger::ERROR, "TENSION CRITIQUE! " + String(battery.voltage) + " V");
  } 
  else if (battery.voltage < 11.0) {
    DebugLogger::println(DebugLogger::WARNING, "Tension basse: " + String(battery.voltage) + " V");
  }
  
  if (battery.temperature > 40.0) {
    DebugLogger::println(DebugLogger::ERROR, "SURCHAUFFE! " + String(battery.temperature) + " °C");
  }
  else if (battery.temperature > 35.0) {
    DebugLogger::println(DebugLogger::WARNING, "Température élevée: " + String(battery.temperature) + " °C");
  }
}

// Fonction pour simuler le changement de mode de débogage
void changeBatteryVerbosity(bool verbose) {
  // Modifie dynamiquement les réglages de débogage
  if (verbose) {
    DebugLogger::enableCategory(DebugLogger::DEBUG);
    DebugLogger::enableCategory(DebugLogger::I2C);
    DebugLogger::enableCategory(DebugLogger::BATTERY);
    DebugLogger::println(DebugLogger::INFO, "Mode verbosité élevée activé");
  } else {
    DebugLogger::disableCategory(DebugLogger::DEBUG);
    DebugLogger::disableCategory(DebugLogger::I2C);
    // Garder BATTERY activé pour les informations essentielles
    DebugLogger::println(DebugLogger::INFO, "Mode verbosité standard activé");
  }
}

void setup() {
  // Définir une configuration complète de niveaux de débogage
  DebugLogger::DebugLevelInfo debugLevels[] = {
    { "AUCUN", false },
    { "ERREUR", true },
    { "AVERTISSEMENT", true },
    { "INFO", true },
    { "DEBUG", false },
    { "BATTERIE", true },
    { "I2C", false },
    { "INFLUXDB", false },
    { "TEMPS", true },
    { "WIFI", true },
    { "SD", false },
    { "SPIFF", false },
    { "WEB", false }
  };
  
  // Initialisation avec Serial2 à 115200 bauds
  // Note: Sur certains appareils, il peut être nécessaire d'utiliser Serial à la place
  DebugLogger::begin(&Serial, 115200, debugLevels, enumSize(DebugLogger::DebugLevel));
  
  DebugLogger::println(DebugLogger::INFO, "Système de surveillance de batterie");
  DebugLogger::println(DebugLogger::INFO, "Version 2.1.0 - Mode avancé");
  DebugLogger::println(DebugLogger::INFO, "Initialisation des capteurs...");
  
  // Simuler une initialisation
  delay(1000);
  
  DebugLogger::println(DebugLogger::INFO, "Système prêt!");
  
  // Afficher l'état initial de la batterie
  logBatteryStatus();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Échantillonner les données à intervalles réguliers
  if (currentTime - lastSampleTime >= samplingInterval) {
    lastSampleTime = currentTime;
    
    // Générer de nouvelles données
    sampleBatteryData();
    
    // Journaliser les données standard
    logBatteryStatus();
    
    // Vérifier les conditions d'erreur
    checkForErrors();
    
    // Générer des messages de débogage détaillés
    if (DebugLogger::isCategoryEnabled(DebugLogger::DEBUG)) {
      DebugLogger::println(DebugLogger::DEBUG, "Temps écoulé: " + String(currentTime/1000) + " s");
      DebugLogger::println(DebugLogger::DEBUG, "Résistance interne estimée: " + String(random(50, 150)/1000.0) + " Ohm");
    }
    
    // Simuler des communications I2C
    if (DebugLogger::isCategoryEnabled(DebugLogger::I2C)) {
      DebugLogger::println(DebugLogger::I2C, "Lecture I2C adresse 0x48: " + String(random(0, 1023)));
      DebugLogger::println(DebugLogger::I2C, "Écriture I2C adresse 0x49: OK");
    }
    
    // Alterner entre les modes verbeux et standard toutes les 5 mesures
    if ((currentTime / samplingInterval) % 10 == 0) {
      changeBatteryVerbosity(true);  // Mode verbeux
    } 
    else if ((currentTime / samplingInterval) % 5 == 0) {
      changeBatteryVerbosity(false);  // Mode standard
    }
  }
  
  // Gestion des erreurs en temps réel
  if (systemError) {
    // Le code d'erreur alternera entre activé/désactivé pour simuler un clignotement
    if ((millis() / 500) % 2 == 0) {
      DebugLogger::print(DebugLogger::ERROR, "! ");
    } else {
      DebugLogger::print(DebugLogger::ERROR, "* ");
    }
    
    // Simuler une récupération d'erreur après quelques clignotements
    if (random(0, 100) < 20) {  // 20% de chance de récupération
      systemError = false;
      DebugLogger::println(DebugLogger::INFO, "Système rétabli après erreur");
    }
  }
  
  delay(100);  // Courte pause pour économiser les ressources
}
