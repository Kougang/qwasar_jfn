window.onload = function () {
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  // !!! Les fonctions !!!

  // drawForme()
  //   Dessine une forme à l'écran
  //   Variable utilisées :
  //		numForme : numéro de la forme à afficher (tableau forme)
  //		rotation : version de la forme à afficher (tableau forme[numForme])
  //		formX : Position horizontale de la forme sur la grille
  //		formY : Position verticale de la forme sur la grille
  function drawForme(numForme, formX, formY, rotation) {
    for (x = 0; x < forme[numForme][rotation].length; x++) {
      for (y = 0; y < forme[numForme][rotation].length; y++) {
        if (forme[numForme][rotation][y][x] == 1) {
          ctx.fillStyle = couleursFormes[numForme][1]; // Couleur du contour de la forme
          ctx.fillRect(
            (formX + x) * CARREAU,
            (formY + y) * CARREAU,
            CARREAU,
            CARREAU
          ); // Contour de la forme
          ctx.fillStyle = couleursFormes[numForme][0]; // Couleur de remplissage de la forme
          ctx.fillRect(
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

  function drawGrille() {
    for (let x = 0; x < LARGEUR_GRILLE; x++) {
      for (let y = 0; y < HAUTEUR_GRILLE; y++) {
        if (grille[x][y] > -1) {
          ctx.fillStyle = couleursFormes[grille[x][y]][1]; // Couleur du contour de la forme
          ctx.fillRect(x * CARREAU, y * CARREAU, CARREAU, CARREAU); // Contour de la forme
          ctx.fillStyle = couleursFormes[grille[x][y]][0]; // Couleur de remplissage de la forme
          ctx.fillRect(
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

  // numForme = nouvelleForme();
  // formeSuivante = nouvelleForme();

  function refreshCanvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.clearRect(0, 0, LARGEUR_GRILLE * CARREAU, HAUTEUR_GRILLE * CARREAU);

    formY++; // Faire descendre la pièce

    if (collision()) {
      formY--; // En cas de collision on revient en arrière
      copierFormeDansLaGrille();
      formY = Y_INITIAL; // Une nouvelle forme arrive en haut du canvas
      formX = X_INITIAL;
      rotation = 0;

      numForme = formeSuivante; // Copier la forme suivante
      formeSuivante = nouvelleForme();
      verifierLignes();
    }
    // if (formY == HAUTEUR_GRILLE) {
    //   // Gérez la fin du jeu, par exemple :
    //   alert("Game Over");
    //   return;
    // }
    // // Quand une forme arrive en bas ou se pose sur une autre pièce
    // if (formY > HAUTEUR_GRILLE - 3) {
    //   formY = 0;
    //   numForme = formeSuivante; // Copier la forme suivante
    //   formeSuivante = nouvelleForme(); // Générer une nouvelle forme suivante aléatoire
    // }
    // // Si la pièce atteint le bas, la faire remonter au sommet
    // if (formY > HAUTEUR_GRILLE - 3) {
    //   formY = 0;
    // }
    drawGrille(); // Afficher la grille
    drawForme(formeSuivante, LARGEUR_GRILLE + 1, 2, 0);
    ctx.fillStyle = "blue";
    ctx.fillRect(LARGEUR_GRILLE * CARREAU, 0, 1, HAUTEUR_GRILLE * CARREAU);
    drawForme(numForme, formX, formY, rotation);

    dansConditionCollisionComptePoint == 1
      ? ctx.fillText("score: " + score * 10, LARGEUR_GRILLE * CARREAU + 10, 60)
      : dansConditionCollisionComptePoint == 0;

    intervalId = setTimeout(refreshCanvas, delay);
  }

  ///////////////////////////////////////////////////////
  // inti()
  //   Initialisation du canvas
  function init() {
    canvas = document.getElementById("idcanvas");
    // canvas1 = document.getElementById("idcanvas1");
    canvas.width = (LARGEUR_GRILLE + 5) * CARREAU;
    // canvas.width = LARGEUR_GRILLE * CARREAU;
    canvas.height = HAUTEUR_GRILLE * CARREAU;
    ctx = canvas.getContext("2d");
    // ctx1 = canvas.getContext("2d");
    // fprme aleatoire et detection de la suivante
    numForme = nouvelleForme();
    formeSuivante = nouvelleForme();

    // Initialisation du tableau grille
    initGrille();

    refreshCanvas();

    // // Affichage de "Prochaine forme"
    ctx.fillStyle = "blue";
    ctx.font = "20px Arial";
    ctx.fillText("Prochaine forme", LARGEUR_GRILLE * CARREAU + 10, 30);
    // Affichage de "Prochaine forme" dans le deuxième canvas

    // ctx1.fillStyle = "blue";
    // ctx1.font = "20px Arial";
    // ctx1.fillText("Prochaine forme", 10, 30); // Position ajustée

    // Trait vertical noir dans le deuxième canvas
    ctx.fillRect(0, 0, 1, HAUTEUR_GRILLE * CARREAU);

    // Trait vertical noir
    ctx.fillRect(LARGEUR_GRILLE * CARREAU, 0, 1, HAUTEUR_GRILLE * CARREAU);
  }
  // !!! Fin des fonctions !!!
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  function moveLeft() {
    formX = Math.max(formX - 1, 0); // Déplacer vers la gauche, en restant dans les limites du canvas
  }

  function moveRight() {
    formX = Math.min(formX + 1, LARGEUR_GRILLE - 3); // Déplacer vers la droite, en restant dans les limites du canvas
  }

  // Gestion des évènements clavier
  window.addEventListener(
    "keydown",
    function (event) {
      var key = event.key;
      switch (key) {
        // Remarque : Pour connaitre les "keycodes" : https://keycode.info/
        case "ArrowUp": // flèche haut => rotation horaire de la forme
          temp = rotation;
          rotation++;
          if (rotation > forme[numForme].length - 1) rotation = 0;
          if (collision()) rotation = temp;
          break;

        case "t": // toutche t
          numForme++;
          if (numForme > forme.length - 1) numForme = 0;
          // refreshCanvas();
          break;
        case "ArrowLeft":
          moveLeft();
          break;

        case "ArrowRight":
          moveRight();
          break;
        case " ":
          // Barre d'espacement => augmenter la vitesse de 250
          delay += 50;
          if (delay < 50) delay = 50; // Limiter la vitesse minimale
          clearInterval(intervalId); // Arrêter l'intervalle actuel
          intervalId = setInterval(refreshCanvas, delay); // Redémarrer l'intervalle avec la nouvelle vitesse
          break;
      }
    },
    true
  );

  // !!! Code !!!
  // Seule ligne de code... avec la gestion des évènements clavier

  init();
};
