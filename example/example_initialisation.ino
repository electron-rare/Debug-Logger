#include <DebugLogger.h>

DebugLogger logger;

void setup() {
  // Initialiser le DebugLogger avec les niveaux de débogage par défaut
  Serial.begin(9600);
  logger.begin(&Serial);
  logger.setDefaultDebugLevels();

  // Définir les noms des niveaux de débogage
  logger.setDebugLevelName(DebugLogger::ERROR, "ERREUR");
  logger.setDebugLevelName(DebugLogger::INFO, "INFORMATION");

  // Utiliser les méthodes de DebugLogger
  logger.println("Ceci est un message de log.");
  logger.printlnDebug(DebugLogger::INFO, "Ceci est un message d'information.");
  logger.printlnDebug(DebugLogger::ERROR, "Ceci est un message d'erreur.");
}

void loop() {
  // Code principal
}
