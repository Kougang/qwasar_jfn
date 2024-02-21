window.onload = function () {
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  // !!! Les fonctions !!!

  function drawForme(numForme, formX, formY, rotation, forme, contexte) {
    for (x = 0; x < forme[numForme][rotation].length; x++) {
      for (y = 0; y < forme[numForme][rotation].length; y++) {
        if (forme[numForme][rotation][y][x] == 1) {
          contexte.fillStyle = couleursFormes[numForme][1]; // Couleur du contour de la forme
          contexte.fillRect(
            (formX + x) * CARREAU,
            (formY + y) * CARREAU,
            CARREAU,
            CARREAU
          ); // Contour de la forme
          contexte.fillStyle = couleursFormes[numForme][0]; // Couleur de remplissage de la forme
          contexte.fillRect(
            (formX + x) * CARREAU + 1,
            (formY + y) * CARREAU + 1,
            CARREAU - 2,
            CARREAU - 2
          ); // Remplissage de la forme
        }
      }
    }
  }
  ///////////////////////////////////////////////////////

  function drawGrille(contexte) {
    for (let x = 0; x < LARGEUR_GRILLE; x++) {
      for (let y = 0; y < HAUTEUR_GRILLE; y++) {
        if (grille[x][y] > -1) {
          contexte.fillStyle = couleursFormes[grille[x][y]][1]; // Couleur du contour de la forme
          contexte.fillRect(x * CARREAU, y * CARREAU, CARREAU, CARREAU); // Contour de la forme
          contexte.fillStyle = couleursFormes[grille[x][y]][0]; // Couleur de remplissage de la forme
          contexte.fillRect(
            x * CARREAU + 1,
            y * CARREAU + 1,
            CARREAU - 2,
            CARREAU - 2
          ); // Remplissage de la forme
        }
      }
    }
  }

  function nouvelleForme() {
    return Math.floor(Math.random() * forme.length);
  }

  function refreshCanvas() {
    ``;
    // netoyage canvas 1
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // netoyage canvas 2
    ctx1.clearRect(0, 0, canvas1.width, canvas1.height);

    formY++; // Faire descendre la pièce
    scoreFormY += 1;
    // console.log("score fromy", scoreFormY);
    //   // Vérifier si la collision se produit à une hauteur critique (0 ou 1)
    if (collision()) {
      // condition d arret du jeu
      if (formY <= 1 && !isGameOver) {
        formY--;
        // Le joueur a perdu
        isGameOver = true;
        clearInterval(intervalId);
        document.getElementById("endMessageText").innerText = "Perdu !";
        document.getElementById("endMessage").style.display = "block";

        // !!!zone audio
        // Chargez les fichiers audio au démarrage du jeu
        const gameStartAudio = loadAudio(
          "gameStartAudio",
          "./son/gameover.wav"
        );
        // joue la musique de debut au click sur le boutton play
        var startButton = document.getElementById("play");
        startButton.addEventListener("click", function () {
          // jouer si click
          gameStartAudio.play();
        });
      } else {
        delay = 250;
        formY--; // En cas de collision on revient en arrière
        copierFormeDansLaGrille();
        formY = Y_INITIAL; // Une nouvelle forme arrive en haut du canvas
        formX = X_INITIAL;
        rotation = 0;

        numForme = formeSuivante; // Copier la forme suivante
        formeSuivante = nouvelleForme();
        verifierLignes();
        //reintialisation de la vitesse apres aveoir presse sur la barre d'espace
      }
    }

    drawGrille(ctx); // Afficher la grille
    drawForme(formeSuivante, LARGEUR_GRILLE - 10, 2, 0, forme, ctx1);
    drawForme(numForme, formX, formY, rotation, forme, ctx);

    // score += formY;
    // console.log("score normal", lines);
    document.getElementById("score").innerText = scoreFormY;
    document.getElementById("lines").innerText = score; // Remplacez lines par votre variable correspondante
    document.getElementById("level").innerText = level;
    if (score == 10) {
      level += 1;
      document.getElementById("level").innerText = level;
    }

    if (!isGameOver) {
      clearInterval(intervalId);
      intervalId = setInterval(refreshCanvas, delay);
    }
  }

  ///////////////////////////////////////////////////////
  // inti()
  //   Initialisation du canvas
  function init() {
    canvas = document.getElementById("idcanvas");
    canvas.width = LARGEUR_GRILLE * CARREAU;
    canvas.height = HAUTEUR_GRILLE * CARREAU;
    ctx = canvas.getContext("2d");

    numForme = nouvelleForme();
    formeSuivante = nouvelleForme();

    canvas1 = document.getElementById("idcanvas1");
    canvas1.width = 200;
    canvas1.height = 200;
    ctx1 = canvas1.getContext("2d");
    // Initialisation du tableau grille
    initGrille();

    refreshCanvas();

    ctx1.fillText("Prochaine forme", LARGEUR_GRILLE * CARREAU + 10, 30);
    // Trait vertical noir dans le deuxième canvas
    ctx1.fillRect(0, 0, 1, HAUTEUR_GRILLE * CARREAU);
    // Trait vertical noir
    ctx.fillRect(LARGEUR_GRILLE * CARREAU, 0, 1, HAUTEUR_GRILLE * CARREAU);

    // !!!zone audio
    // Chargez les fichiers audio au démarrage du jeu
    const gameStartAudio = loadAudio("gameStartAudio", "./son/success.wav");
    // joue la musique de debut au click sur le boutton play
    var startButton = document.getElementById("play");
    startButton.addEventListener("click", function () {
      // jouer si click
      gameStartAudio.play();
    });
  }
  // !!! Fin des fonctions !!!

  // import { drawForme, drawGrille, nouvelleForme, refreshCanvas } from "./App";

  // !!!zone lier aux evenements!!!
  function moveLeft() {
    formX = Math.max(formX - 1, 0); // Déplacer vers la gauche, en restant dans les limites du canvas
  }

  function moveRight() {
    formX = Math.min(formX + 1, LARGEUR_GRILLE - 3); // Déplacer vers la droite, en restant dans les limites du canvas
  }

  // !!!Gestion des évènements clavier!!!
  controlPressed = false;
  shiftPressed = false;
  cPressed = false;
  zPressed = false;
  window.addEventListener(
    "keydown",
    function (event) {
      event.preventDefault();
      let key = event.key;
      switch (key) {
        case "1":
        case "5":
        case "9":
        case "x": // flèche x et haut => rotation horaire de la forme
        case "ArrowUp":
          temp = rotation;
          forme = forme;
          rotation++;
          if (rotation > forme[numForme].length - 1) rotation = 0;
          if (collision()) rotation = temp;

          // Chargez les fichiers audio au démarrage du jeu
          const gameStartAudio2 = loadAudio(
            "gameStartAudio",
            "./son/rotate.wav"
          );
          // jouer si click
          gameStartAudio2.play();
          break;

        case "z": // Z => rotation anti-horaire de la forme
          zPressed = true;
          break;

        case "3": //  rotation anti-horaire de la forme
        case "7":
          forme = formeAntiHoraire; // changement de tableau
          temp = rotation;
          rotation++;
          if (rotation > forme[numForme].length - 1) rotation = 0;
          if (collision()) rotation = temp;
          break;

        case "t": // toutche t
          numForme++;
          if (numForme > forme.length - 1) numForme = 0;
          // refreshCanvas();
          // Chargez les fichiers audio au démarrage du jeu
          const gameStartAudio1 = loadAudio("gameStartAudio", "./son/move.wav");
          // jouer si click
          gameStartAudio1.play();
          break;

        case "4":
        case "ArrowLeft":
          moveLeft();
          break;

        case "6":
        case "ArrowRight":
          moveRight();
          break;

        // case "2":
        //   delay -= 200;
        //   if (delay < 50) delay = 50; // Limiter la vitesse minimale
        //   // intervalId = setInterval(refreshCanvas, delay); // Redémarrer l'intervalle avec la nouvelle vitesse
        //   break;
        case " ":
        case "2":
          // Annuler le comportement par défaut
          delay -= 200;
          if (delay < 50) delay = 50; // Limiter la vitesse minimale
          // clearInterval(intervalId);
          // intervalId = setInterval(refreshCanvas, delay); // Redémarrer l'intervalle avec la nouvelle vitesse
          break;

        case "8":
        case "ArrowDown": // Flèche bas => descente rapide
          while (!collision()) {
            formY++;
          }
          formY--; // Revenir d'un pas en arrière car la descente rapide a détecté une collision
          // Chargez les fichiers audio au démarrage du jeu
          const gameStartAudio4 = loadAudio("gameStartAudio", "./son/fall.wav");
          // jouer si click
          gameStartAudio4.play();

          break;

        // case "Enter":
        case "Escape":
        case "F1":
          if (isPaused) {
            // console.log("doit faire play");
            isPaused = false;
            countdown = 3;
            function startCountdown() {
              if (countdown > 0) {
                // console.log("dans startnow");
                document.getElementById("startnowText").innerText = countdown;
                document.getElementById("startnowText").style.display = "block";

                countdown--;
                setTimeout(startCountdown, 1000); // Appeler la fonction après 1 seconde
              } else {
                document.getElementById("startnowText").innerText = ""; // Effacer le texte après le compte à rebours
                document.getElementById("startnowText").style.display = "none";
                // Démarrer le jeu ici, par exemple, appeler votre fonction init()
                intervalId = setInterval(refreshCanvas, delay);
              }
            }
            startCountdown();
          } else {
            // console.log("met le jeu en pause");
            isPaused = true;
            clearInterval(intervalId);
            // clearTimeout(intervalId);
          }
        case "Shift": // Shift => maintenir
          shiftPressed = true;
          break;

        case "c": // C => maintenir
          if (!cPressed) {
            cPressed = true;
          } else {
            cPressed = false;
          }
          break;

        case "Control": // Ctrl => maintenir
          if (!controlPressed) {
            controlPressed = true;
          } else {
            controlPressed = false;
          }

          break;
        //  /////////////////////////////////////////////////////
        // !!relancer le jeu en cas de fin ou collision vers le haut
        case "Enter":
          if (isGameOver) {
            // console.log("dans entrer relancer le jeu");
            // Relancer le jeu
            isGameOver = false;
            initGrille();
            numForme = nouvelleForme();
            formeSuivante = nouvelleForme();
            formY = Y_INITIAL;
            formX = X_INITIAL;
            rotation = 0;
            score = 0; // Ajouter cette ligne si vous souhaitez réinitialiser le score
            scoreFormY = 0;
            level = 0;
            delay = 250;
            intervalId = setInterval(refreshCanvas, delay);

            // netoyage du message perdu de l ecran
            document.getElementById("endMessage").style.display = "none";
          }
          break;
      }
      // control+z => rotation anti horaire
      if (controlPressed && zPressed) {
        forme = formeAntiHoraire; // changement de tableau
        temp = rotation;
        rotation++;
        if (rotation > forme[numForme].length - 1) rotation = 0;
        if (collision()) rotation = temp;
      }
    },
    true
  );

  // !!!fin des evenements!!!

  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  // !!! zone de lancement du code !!!
  // init();
  // let countdown = 3; // Initialiser le compte à rebours à partir de 3

  function startCountdown() {
    if (countdown > 0) {
      console.log("dans startnow");
      document.getElementById("startnowText").innerText = countdown;
      document.getElementById("startnowText").style.display = "block";

      countdown--;
      setTimeout(startCountdown, 1000); // Appeler la fonction après 1 seconde
    } else {
      document.getElementById("startnowText").innerText = ""; // Effacer le texte après le compte à rebours
      document.getElementById("startnowText").style.display = "none";
      // Démarrer le jeu ici, par exemple, appeler votre fonction init()
      init();
    }
  }

  // Ajouter une fonction pour afficher le message de copyright au démarrage
  function showCopyrightMessage() {
    const currentYear = new Date().getFullYear();
    const copyrightMessage = `Tetris © 1985~${currentYear} Tetris Holding. Les logos Tetris`;
    alert(copyrightMessage);
    // Vous pouvez également afficher le message dans un élément HTML spécifique si nécessaire
  }
  showCopyrightMessage();

  // Gérer l'événement de la touche "Play" ou "Enter"
  window.addEventListener("keydown", function (event) {
    let key = event.key;
    if (key === "Enter") {
      startCountdown();
    }
  });

  startCountdown();
};

// export default { drawForme, drawGrille, nouvelleForme, refreshCanvas };
