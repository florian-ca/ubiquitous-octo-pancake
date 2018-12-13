# ubiquitous-octo-pancake
TP CERI - Génie Logiciel Scrum - Parseur d’articles scientifiques en format texte 

Parser utilisé : pdftotext
langage utilisé : c++
fichier c++:parserpdf.cpp

Commande de compilation :
g++ -std=c++11 parserpdf.cpp -o parserpdf

Lancer le programme :
./parserpdf pdftotext fileName.pdf fileOutput.txt
avec :
filename.pdf le nom du fichier à parser (au format pdf)
fileOutput.txt le fichier de sortie

Le document parsé et résumé se trouve dans fileParsed.txt


Le parser fonctionne pour les fichiers(preamble + title + author + abstract) :
-Lin_2004_Rouge.pdf
-Doyle_2005_Automatic Categorization of Author Gender.pdf
-Torres-Moreno_2012_Artex is another text summarizer.pdf
-Levner_2007_Fuzzifying clustering algorithms The case study of MajorClust.pdf
-Alexandrov_2015_A Modified Tripartite Model for Document Representation in Internet Sociology.pdf
-Mikolov_2013_Distributed representations of words and phrases and their compositionality.pdf

et pour la bilbliography le parser fonctionne pour :
-Doyle_2005_Automatic Categorization of Author Gender.pdf
-Torres-Moreno_2012_Artex is another text summarizer.pdf
-Levner_2007_Fuzzifying clustering algorithms The case study of MajorClust.pdf
-Alexandrov_2015_A Modified Tripartite Model for Document Representation in Internet Sociology.pdf
-Mikolov_2013_Distributed representations of words and phrases and their compositionality.pdf


Les autres fichiers sont trop compliqués à parser.
Soit le titre n'est pas sur la premiere ligne soit l'auteur n'est pas directement après le titre.
