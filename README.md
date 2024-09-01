# Formulaire CGI en C++

Ce projet implémente un formulaire de traitement de données en utilisant le langage C++ et le Common Gateway Interface (CGI). Il permet d'afficher des données sous forme de table HTML et de gérer des actions comme l'ajout, la suppression, et le changement de format des données.

## Structure du projet

- `index.html`: Fichier HTML qui affiche le formulaire et les tables de données.
- `main.cpp`: Point d'entrée principal de l'application qui traite les requêtes CGI.
- `Form.hpp`: Fichier d'en-tête qui déclare la classe `Form`.
- `Form.cpp`: Implémentation des méthodes de la classe `Form`.
- `data.txt`: Fichier de données qui stocke les informations soumises via le formulaire.

## Fonctionnalités

- **Affichage de formulaires HTML**: Un formulaire est affiché permettant à l'utilisateur d'ajouter de nouvelles données.
- **Traitement des données**: Les données soumises par l'utilisateur sont traitées et stockées dans un fichier texte (`data.txt`).
- **Affichage des données**: Les données sont affichées dans une table HTML, avec des options pour afficher une version longue ou courte de la table.
- **Suppression de lignes**: Les utilisateurs peuvent supprimer des lignes spécifiques de données en cliquant sur le bouton "Remove".

## Prérequis

- Un compilateur C++ (par exemple, GCC).
- Un serveur HTTP configuré pour exécuter des scripts CGI.
- Les bibliothèques standard de C++.

## Installation

1. Clonez ce dépôt sur votre machine locale:

    ```bash
    git clone https://github.com/Kimbohy/Formulaire-CGI-en-Cpp.git
    ```

2. Compilez le projet en utilisant un compilateur C++:

    ```bash
    g++ -o index.cgi main.cpp Form.cpp
    ```

3. Assurez-vous que le fichier exécutable `index.cgi` a les permissions appropriées pour être exécuté par le serveur web:

    ```bash
    chmod +x index.cgi
    ```

4. Placez `index.cgi` et les autres fichiers nécessaires (comme `data.txt` s'il existe) dans le répertoire CGI de votre serveur HTTP.

## Utilisation

1. Ouvrez un navigateur web et accédez à `index.cgi` via votre serveur HTTP. Vous devriez voir le formulaire de saisie de données.
2. Remplissez les champs du formulaire et soumettez-le. Les données seront ajoutées à la table et stockées dans `data.txt`.
3. Utilisez les options fournies pour afficher les données sous forme de table courte ou longue, ou pour supprimer des entrées.

## Avertissement

- Assurez-vous que `data.txt` a les permissions nécessaires pour la lecture et l'écriture, afin d'éviter des erreurs de fichier.
- Ce projet est conçu à des fins éducatives et n'est pas optimisé pour les environnements de production.

## Auteur

- Lova, alias Kimohy

---

Si vous avez des questions ou des suggestions, n'hésitez pas à ouvrir une *issue* ou à me contacter directement. Merci d'utiliser ce projet!
