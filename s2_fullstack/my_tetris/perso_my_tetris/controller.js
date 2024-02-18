// ici nous implementerons la logique relative au controlleur, il s agit du code executable au declachement des different
// evenements du clavier
// haut,bas,gauche,droite,espace
// Gestion des évènements clavier
window.addEventListener(
  "keydown",
  function (event) {
    var key = event.key;
    switch (key) {
      // Remarque : Pour connaitre les "keycodes" : https://keycode.info/
      case "ArrowUp": // flèche haut => rotation horaire de la forme
        rotation++;
        if (rotation > forme[numForme].length - 1) rotation = 0;
        refreshCanvas();
        break;

      case "t": // toutche t
        numForme++;
        if (numForme > forme.length - 1) numForme = 0;
        refreshCanvas();
        break;
    }
  },
  true
);
