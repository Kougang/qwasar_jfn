// ici nous creons des tableaux de forme et de couleurs neccessaire
// Tableau de couleurs des formes
// Numéro de la forme (du tableau "forme") à afficher

// !!!déclaration des variables !!!
const LARGEUR_GRILLE = 14; // Nombre de cases en largeur
const HAUTEUR_GRILLE = 28; // Nombre de cases en hauteur
const CARREAU = 20; // Taille en pixels d'une case de la grille
let canvas; // Un canvas est un élément HTML dans lequel on peut dessiner des formes
let ctx;

// Position de la forme sur la grille
const X_INITIAL = 5;
const Y_INITIAL = 0;
let formX = X_INITIAL;
let formY = Y_INITIAL;

let numForme = 0;
let rotation = 0;
let delay = 250; // Délai initial en millisecondes
let intervalId; // Identifiant de l'intervalle

// Déclaration du tableau grille
var grille = new Array(LARGEUR_GRILLE);

let formeSuivante;

let score = 0;
let scoreFormY = 0;
let level = 0;

let dansConditionCollisionComptePoint = 0;
let isPaused = false;
let isGameOver = false;

let countdown = 3;
// !!!Tableau de définition des couleurs

let couleursFormes = [
  ["#00FFFF", "#00FF00"], // Couleurs pour la forme 0 (L1-Forme)
  ["#FFFF00", "#00FF00"], // Couleurs pour la forme 1 (L2-Forme)
  ["#800080", "#00FF00"],
  ["008000", "#00FF00"],
  ["#FF0000", "#00FF00"],
  ["#0000FF", "#00FF00"],
  ["#FFA500", "#00FF00"],
];

// !!!Tableau de définition des formes

// Tableau de définition des formes
let forme = new Array();
let formeAntiHoraire = new Array();
// L1-Forme
forme[0] = [
  // L1-Forme
  [
    // rotation 0
    [0, 0, 0],
    [1, 0, 0],
    [1, 1, 1],
  ],
  [
    // rotation 1
    [0, 1, 1],
    [0, 1, 0],
    [0, 1, 0],
  ],
  [
    // rotation 2
    [0, 0, 0],
    [1, 1, 1],
    [0, 0, 1],
  ],
  [
    // rotation 3
    [0, 1, 0],
    [0, 1, 0],
    [1, 1, 0],
  ],
];
// L1-formeAntiHoraire
formeAntiHoraire[0] = [
  // L1-Forme
  [
    // rotation 0
    [0, 0, 0],
    [1, 0, 0],
    [1, 1, 1],
  ],
  [
    // rotation 1
    [0, 1, 0],
    [0, 1, 0],
    [1, 1, 0],
  ],
  [
    // rotation 2
    [0, 0, 0],
    [1, 1, 1],
    [0, 0, 1],
  ],
  [
    // rotation 3
    [0, 1, 1],
    [0, 1, 0],
    [0, 1, 0],
  ],
];

// L2-Forme
forme[1] = [
  // L2-Forme
  [
    // rotation 0
    [0, 0, 0],
    [0, 0, 1],
    [1, 1, 1],
  ],
  [
    // rotation 1
    [0, 1, 0],
    [0, 1, 0],
    [0, 1, 1],
  ],
  [
    // rotation 2
    [0, 0, 0],
    [1, 1, 1],
    [1, 0, 0],
  ],
  [
    // rotation 3
    [1, 1, 0],
    [0, 1, 0],
    [0, 1, 0],
  ],
];
// L2-formeAntiHoraire
formeAntiHoraire[1] = [
  [
    // rotation 0
    [0, 0, 0],
    [0, 0, 1],
    [1, 1, 1],
  ],
  [
    // rotation 1
    [1, 1, 0],
    [0, 1, 0],
    [0, 1, 0],
  ],
  [
    // rotation 2
    [0, 0, 0],
    [1, 1, 1],
    [1, 0, 0],
  ],
  [
    // rotation 3
    [0, 1, 0],
    [0, 1, 0],
    [0, 1, 1],
  ],
];

// J1-Forme 2
forme[2] = [
  // J1-Forme 2
  [
    // rotation 0 (cette forme là n'a besoin que de 2 rotations)
    [0, 0, 0],
    [0, 1, 1],
    [1, 1, 0],
  ],
  [
    // rotation 1
    [0, 1, 0],
    [0, 1, 1],
    [0, 0, 1],
  ],
];
// J1-formeAntiHoraire
formeAntiHoraire[2] = [
  [
    // rotation 0 (cette forme là n'a besoin que de 2 rotations)
    [0, 0, 0],
    [0, 1, 1],
    [1, 1, 0],
  ],

  [
    // rotation 1
    [1, 0, 0],
    [1, 1, 0],
    [0, 1, 0],
  ],
];

// J2-Forme 2
forme[3] = [
  // J2-Forme 2
  [
    // rotation 0 (cette forme là n'a besoin que de 2 rotations)
    [0, 0, 0],
    [1, 1, 0],
    [0, 1, 1],
  ],
  [
    // rotation 1
    [0, 0, 1],
    [0, 1, 1],
    [0, 1, 0],
  ],
];
// J2-formeAntiHoraire
formeAntiHoraire[3] = [
  // J2-Forme 2
  [
    // rotation 0 (cette forme là n'a besoin que de 2 rotations)
    [0, 0, 0],
    [1, 1, 0],
    [0, 1, 1],
  ],
  [
    // rotation 1
    [0, 1, 0],
    [1, 1, 0],
    [1, 0, 0],
  ],
];

// carre-forme
forme[4] = [
  // carre-forme
  [
    // rotation 0
    [1, 1],
    [1, 1],
  ],
];
// carre-formeAntiHoraire
formeAntiHoraire[4] = [
  // carre-forme
  [
    // rotation 0
    [1, 1],
    [1, 1],
  ],
];

// barre-forme
forme[5] = [
  // barre-forme
  [
    // rotation 0
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [1, 1, 1, 1],
    [0, 0, 0, 0],
  ],
  [
    // rotation 1
    [0, 0, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 0],
  ],
];
// barre-formeAntiHoraire
formeAntiHoraire[5] = [
  // barre-forme
  [
    // rotation 0
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [1, 1, 1, 1],
    [0, 0, 0, 0],
  ],
  [
    // rotation 1
    [0, 0, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 0],
  ],
];

// T-forme
forme[6] = [
  // T-forme
  [
    // rotation 0
    [0, 1, 0],
    [1, 1, 1],
    [0, 0, 0],
  ],

  [
    // rotation 1
    [0, 1, 0],
    [0, 1, 1],
    [0, 1, 0],
  ],

  [
    [0, 0, 0],
    [1, 1, 1],
    [0, 1, 0],
  ],
  [
    [0, 1, 0],
    [1, 1, 0],
    [0, 1, 0],
  ],
];
// T-formeAntiHoraire
formeAntiHoraire[6] = [
  // T-forme
  [
    // rotation 0
    [0, 1, 0],
    [1, 1, 1],
    [0, 0, 0],
  ],

  [
    // rotation 1
    [0, 1, 0],
    [1, 1, 0],
    [0, 1, 0],
  ],

  [
    [0, 0, 0],
    [1, 1, 1],
    [0, 1, 0],
  ],
  [
    [0, 1, 0],
    [0, 1, 1],
    [0, 1, 0],
  ],
];

//  { numForme, rotation, couleursFormes, forme };
