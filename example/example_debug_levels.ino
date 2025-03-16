#include <DebugLogger.h>

DebugLogger logger;

void setup() {
  // Initialiser le DebugLogger avec des niveaux de débogage spécifiques pour un microcontrôleur programmé avec le langage Arduino
  Serial.begin(9600);
  DebugLogger::DebugLevel levels[] = {DebugLogger::NONE, DebugLogger::ERROR, DebugLogger::WARNING, DebugLogger::NONE, DebugLogger::DEBUG};
  size_t numLevels = sizeof(levels) / sizeof(levels[0]);
  logger.begin(&Serial, 9600, levels, numLevels);

  // Ajouter un nouveau niveau de débogage
  logger.addDebugLevel("CUSTOM");

  // Définir les noms des niveaux de débogage
  logger.setDebugLevelName(DebugLogger::DEBUG, "DEBUGGING");

  // Vérifier si un niveau de débogage est activé
  bool isEnabled = logger.isCategoryEnabled(DebugLogger::DEBUG);
  Serial.print("DEBUG level is ");
  Serial.println(isEnabled ? "enabled" : "disabled");

  // Afficher des messages de débogage
  logger.printDebug(DebugLogger::DEBUG, "Ceci est un message de débogage.");
  logger.printlnDebug(DebugLogger::DEBUG, "Ceci est un message de débogage avec saut de ligne.");
}

void loop() {
  // Code principal
}
