# Exemples DebugLogger

Ce répertoire contient des exemples d'utilisation de la bibliothèque DebugLogger.

## Exemples disponibles

### BasicDebugLogger
Exemple de base montrant les fonctionnalités essentielles de DebugLogger :
- Initialisation avec des niveaux de débogage prédéfinis
- Affichage de messages avec différents niveaux de sévérité
- Activation/désactivation dynamique des catégories de débogage
- Vérification conditionnelle des niveaux activés

### AdvancedDebugLogger
Exemple avancé démontrant des utilisations plus sophistiquées :
- Configuration complète des niveaux de débogage
- Utilisation pour surveiller un système de batterie simulé
- Changement dynamique des niveaux de verbosité
- Gestion d'erreurs et affichage conditionnel
- Simulation de différents types de données de débogage (I2C, batterie, etc.)

## Utilisation

Pour utiliser ces exemples :

1. Ouvrez l'IDE Arduino
2. Allez dans Fichier > Exemples > DebugLogger
3. Choisissez l'un des exemples
4. Téléversez le code sur votre carte Arduino/ESP
5. Ouvrez le moniteur série à 115200 bauds pour voir les résultats

## Personnalisation

Ces exemples peuvent être adaptés à vos besoins spécifiques. Vous pouvez :

- Modifier les niveaux de débogage activés
- Changer les messages affichés
- Adapter les exemples pour travailler avec différents capteurs
- Utiliser d'autres ports série si votre carte en dispose

## Remarques

- Certains exemples peuvent nécessiter une carte disposant de plusieurs ports série
- Ajustez les baudrates selon vos besoins
- Sur certaines plateformes, l'appel à `ESP.getFreeHeap()` peut ne pas être disponible
