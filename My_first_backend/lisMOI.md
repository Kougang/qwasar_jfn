Installation des dépendances :
Assurez-vous que Node.js est installé sur votre machine. Ensuite, créez un fichier package.json à la racine de votre projet avec la commande suivante :

bash
Copy code
npm init -y
Ensuite, installez Express.js avec :

bash
Copy code
npm install express
Exécution de l'application :
Enregistrez votre script dans un fichier, par exemple app.js. Ensuite, exécutez votre application avec la commande :

bash
Copy code
node app.js
Tests avec cURL :
Utilisez cURL pour envoyer des requêtes HTTP à votre serveur. Voici quelques exemples :

Pour obtenir une chanson aléatoire :

bash
Copy code
curl http://localhost:8080
Pour obtenir la date de naissance de Frank Sinatra :

bash
Copy code
curl http://localhost:8080/birth_date
Pour obtenir la ville de naissance de Frank Sinatra :

bash
Copy code
curl http://localhost:8080/birth_city
Pour obtenir les noms des femmes de Frank Sinatra :

bash
Copy code
curl http://localhost:8080/wives
Pour rediriger vers la photo de Frank Sinatra :

bash
Copy code
curl http://localhost:8080/picture
Pour accéder à la page publique :

bash
Copy code
curl http://localhost:8080/public
Pour accéder à la page protégée (authentification requise) :

bash
Copy code
curl -u admin:admin http://localhost:8080/protected
Assurez-vous d'ajuster les URLs si vous exécutez le serveur sur une machine distante.

Tester dans le navigateur :
Ouvrez votre navigateur et accédez aux différentes URL (http://localhost:8080, http://localhost:8080/birth_date, etc.) pour voir les réponses directement dans le navigateur.

Ces étapes devraient vous permettre de tester toutes les fonctionnalités de votre application. N'hésitez pas à poser des questions spécifiques sur un aspect particulier si nécessaire !
