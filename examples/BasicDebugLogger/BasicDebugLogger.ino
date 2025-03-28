/*
 * Exemple basique d'utilisation de la bibliothèque DebugLogger
 * 
 * Cet exemple montre comment initialiser et utiliser les fonctionnalités
 * essentielles de la bibliothèque DebugLogger.
 * 
 * Créé par Clément Saillant, 2025.
 */

#include <DebugLogger.h>

// Compteur pour simuler une activité
int counter = 0;

void setup() {
  // Définir les niveaux de débogage que nous souhaitons activer
  DebugLogger::DebugLevelInfo debugLevels[] = {
    { "ERROR", true },     // Toujours activer les erreurs
    { "WARNING", true },   // Activer les avertissements
    { "INFO", true },      // Activer les informations
    { "DEBUG", false },    // Désactiver le débogage détaillé pour l'instant
    { "BATTERY", true }    // Activer les informations de batterie
  };
  
  // Initialiser le DebugLogger avec les niveaux définis
  // Par défaut, utilise Serial à 115200 bauds
  DebugLogger::begin(debugLevels, 5);
  
  // Afficher quelques messages au démarrage
  DebugLogger::println(DebugLogger::INFO, "Application démarrée");
  DebugLogger::println(DebugLogger::INFO, "Version 1.0.0");
  
  // Simuler un avertissement
  DebugLogger::println(DebugLogger::WARNING, "Niveau de batterie inférieur à 30%");
}

void loop() {
  // Incrémenter le compteur
  counter++;
  
  // Afficher une information de compteur périodique
  if (counter % 10 == 0) {
    DebugLogger::println(DebugLogger::INFO, "Compteur: " + String(counter));
  }
  
  // Simuler une information de batterie périodique
  if (counter % 20 == 0) {
    float batteryVoltage = 11.5 + (random(0, 100) / 100.0);
    DebugLogger::println(DebugLogger::BATTERY, "Tension: " + String(batteryVoltage) + "V");
  }
  
  // Simuler une erreur occasionnelle
  if (counter % 50 == 0) {
    DebugLogger::println(DebugLogger::ERROR, "Erreur de communication détectée!");
  }
  
  // Vérifier si le mode DEBUG est activé avant d'exécuter du code coûteux
  if (DebugLogger::isCategoryEnabled(DebugLogger::DEBUG)) {
    // Ce code ne s'exécutera que si le mode DEBUG est actif
    String detailedInfo = "Variables système: ";
    detailedInfo += "Mémoire libre: " + String(ESP.getFreeHeap()) + " bytes, ";
    detailedInfo += "Compteur: " + String(counter);
    
    DebugLogger::println(DebugLogger::DEBUG, detailedInfo);
  }
  
  // Activer dynamiquement le mode DEBUG tous les 100 cycles
  if (counter == 100) {
    DebugLogger::enableCategory(DebugLogger::DEBUG);
    DebugLogger::println(DebugLogger::INFO, "Mode DEBUG activé");
  }
  
  // Désactiver le mode DEBUG après quelques cycles supplémentaires
  if (counter == 110) {
    DebugLogger::disableCategory(DebugLogger::DEBUG);
    DebugLogger::println(DebugLogger::INFO, "Mode DEBUG désactivé");
  }
  
  delay(500);  // Pause pour ne pas saturer la sortie série
}
