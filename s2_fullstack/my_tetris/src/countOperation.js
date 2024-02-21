function effaceLigne(numeroLigne) {
  // Efface la ligne spécifiée
  for (let y = numeroLigne; y > 0; y--) {
    for (let x = 0; x < LARGEUR_GRILLE; x++) {
      grille[x][y] = grille[x][y - 1];
    }
  }
  // Ajoute une nouvelle ligne vide en haut
  for (let x = 0; x < LARGEUR_GRILLE; x++) {
    grille[x][0] = -1;
  }
}

// Appel de la fonction pour effacer une ligne (par exemple, la ligne 5)
// effaceLigne(1);

function verifierLignes() {
  for (let y = 0; y < HAUTEUR_GRILLE; y++) {
    let ligneComplete = true;

    // Vérifie si la ligne est complète
    for (let x = 0; x < LARGEUR_GRILLE; x++) {
      if (grille[x][y] === -1) {
        ligneComplete = false;
        break;
      }
    }
    // Si la ligne est complète, l'efface et incrémente le compteur
    if (ligneComplete) {
      effaceLigne(y);
      score++;
      dansConditionCollisionComptePoint = 1;
      //   alert(score);
      y--; // Réexamine la ligne actuelle après le décalage vers le bas
    }
  }
}

// export default { effaceLigne, verifierLignes };
