
# Parseur PDF

TP CERI - Génie Logiciel Scrum - Parseur d’articles scientifiques en format texte 

## Sommaire

* [Technologies utilisées](#usedtech)
* [Dépendances](#requirements)
* [Compiler](#compile)
* [Utilisation](#utilisation)

## Technologies utilisées

Nous avons utilisé C++ pour développer le parser. Nous utilisons aussi des commandes UNIX et la commande pdftotext.

## Dépendances

* Système d'exploitation : basé sur UNIX
* Programme utilisé pour parser les PDF en format texte : pdftotext
* Langage utilisé : c++
* Nom de l'exécutable à lancer pour parser un article :  parsepdf
* Sources c++ : parserpdf.cpp

## Compiler

Commande de compilation :
```
$ g++ -std=c++11 parserpdf.cpp -o parserpdf
```

## Utilisation 

Lancer le programme :
```
$ ./parserpdf -x pdftotext fileName.pdf fileOutput.xml
$ ./parserpdf -t pdftotext fileName.pdf fileOutput.txt

avec :
filename.pdf le nom du fichier à parser (au format pdf)
fileOutput.txt le fichier de sortie

-x : Résultat en XML
-t : Résultat en texte
```


## Notes

Le parser fonctionne pour les fichiers (preamble + title + author + abstract+ bibliography, avec les options -t et -x):
* Lin_2004_Rouge.pdf
* Doyle_2005_Automatic Categorization of Author Gender.pdf
* Torres-Moreno_2012_Artex is another text summarizer.pdf
* Levner_2007_Fuzzifying clustering algorithms The case study of MajorClust.pdf
* Alexandrov_2015_A Modified Tripartite Model for Document Representation in Internet Sociology.pdf
* Mikolov_2013_Distributed representations of words and phrases and their compositionality.pdf

Les autres fichiers sont trop compliqués à parser.
Soit le titre n'est pas sur la premiere ligne soit l'auteur n'est pas directement après le titre.

