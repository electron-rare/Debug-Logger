#include <DebugLogger.h>

DebugLogger logger;

void setup() {
  // Initialiser le DebugLogger avec les niveaux de débogage par défaut
  Serial.begin(9600);
  logger.begin(&Serial);
  logger.setDefaultDebugLevels();

  // Définir les noms des niveaux de débogage
  logger.setDebugLevelName(DebugLogger::INFO, "INFORMATION");

  // Afficher des messages avec un préfixe personnalisé
  logger.printWithPrefix(DebugLogger::INFO, "INFO: ", "Ceci est un message d'information.");
  logger.printlnWithPrefix(DebugLogger::INFO, "INFO: ", "Ceci est un message d'information avec saut de ligne.");
}

void loop() {
  // Code principal
}
