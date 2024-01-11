
require 'json'

def my_data_process(data)
  # Créer un tableau pour stocker les en-têtes des colonnes
  headers = data[0].split(',')

  # Créer un hash pour stocker les résultats
  result = {}

  # Parcourir les en-têtes des colonnes
  headers.each do |column|
    # Ignorer les colonnes FirstName, LastName, UserName et Coffee Quantity
    next if ['FirstName', 'LastName', 'UserName', 'Coffee Quantity'].include?(column)

    # Créer un hash vide pour stocker les valeurs et leurs occurrences
    values_hash = {}

    # Parcourir les lignes de données
    data[1..-1].each do |line|
      # Séparer les valeurs de la ligne
      values = line.split(',')

      # Récupérer l'index de la colonne actuelle dans la ligne
      column_index = headers.index(column)

      # Récupérer la valeur de la colonne actuelle dans la ligne
      value = values[column_index]

      # Incrémenter le compteur d'occurrences de la valeur actuelle
      values_hash[value] ||= 0
      values_hash[value] += 1
    end

    # Ajouter le hash des valeurs et occurrences à l'ensemble des résultats
    result[column] = values_hash
  end

  # Convertir le hash des résultats en une chaîne JSON
  return result.to_json
end


=begin
Ruby Quest06	My Data Process
Submit directory	ex02
Submit file	my_data_process.rb
Description
We have been provided with a dataset of sales from My Online Coffee Shop. It's a CSV (Comma Separated Values) (each column is separated by , and each line is separated by  ).
Our goal will be to identify customers who are more likely to buy coffee online.

This time we will need to create a function with code logic, not just return the solution hard coded. :D

Data management is a hard problem. To better solve this hard problem, we will split them into smaller ones.

Here is our second step: data transformation. This exercise follows step one.

You will receive the output of your function my_data_transform.

Our function will group the data and it will become a Hash of hash. (Wow.)
Example:
"{'Gender': {'Male': 22, 'Female': 21}, 'Email': {'yahoo.com': 3, 'hotmail.com': 2}, ...}"

We will discard the column FirstName, LastName, UserName and Coffee Quantity from our output.

Your function will be prototyped: def my_data_process
It will take a string array which is the output of your function my_data_transform, it will return a json string of hash of hash following this format:
{COLUMN: {Value1: nbr_of_occurence_of_value_1, Value2: nbr_of_occurence_of_value_2, ...}, ...}
Order of Column will be the order they are in the header of the CSV (Gender first then Email, etc)
Order of the Value will be the order they appear in each line from top left.
Use STRINGS as keys (=> Do not use any symbol or any fancy things. It doesn't translate well in json. (no :Age => "Age"))

Function prototype (ruby)
##
##
## QWASAR.IO -- my_data_process
##
##
## @param {String[]} param_1
##
## @return {string}
##


def my_data_process(param_1)

end
Example 00

Input: ["Gender,FirstName,LastName,UserName,Email,Age,City,Device,Coffee Quantity,Order At", "Male,Carl,Wilderman,carl,yahoo.com,21->40,Seattle,Safari iPhone,2,afternoon", "Male,Marvin,Lind,marvin,hotmail.com,66->99,Detroit,Chrome Android,2,afternoon", "Female,Shanelle,Marquardt,shanelle,hotmail.com,21->40,Las Vegas,Chrome,1,afternoon", "Female,Lavonne,Romaguera,lavonne,yahoo.com,66->99,Seattle,Chrome,2,morning", "Male,Derick,McLaughlin,derick,hotmail.com,41->65,Chicago,Chrome Android,1,afternoon"]
Output:
'{"Gender":{"Male":3,"Female":2},"Email":{"yahoo.com":2,"hotmail.com":3},"Age":{"21->40":2,"66->99":2,"41->65":1},"City":{"Seattle":2,"Detroit":1,"Las Vegas":1,"Chicago":1},"Device":{"Safari iPhone":1,"Chrome Android":2,"Chrome":2},"Order At":{"afternoon":4,"morning":1}}'
Control Center
Group formation - (December 6, 2023 6:20pm)
In Progress - (December 6, 2023 6:20pm)


Access:
READ
WRITE


rochnel-_s
Submitted
Test Review
Finished
Also working on the project

aidarbek_m

ayomide_s

ergashe_ka
Just finished

boriyeva_d
Type
Project
Group Size
1 Participant
Review system
Test Review (Gandalf)
Difficulty
Initiation
Average duration
1 Week
Project's Metadata
Project
id: 272
name: ruby-quest06
visible: True
Qwasar - Terms of Service - Web Accessibility - Privacy Polic
=end