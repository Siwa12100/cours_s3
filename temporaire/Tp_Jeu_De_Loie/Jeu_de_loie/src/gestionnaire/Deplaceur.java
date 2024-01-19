package gestionnaire;
import modele.Case;
import modele.Joueur;

public class Deplaceur {

    public Deplaceur(){}

    public void alternerPosition(Joueur joueurActuel, Joueur joueurSuivant) {
        Case caseActuelle = joueurActuel.getCurrentCase();
        Case caseSuivante = joueurSuivant.getCurrentCase();

        if (caseActuelle != null && caseSuivante != null) {
            // Échange des cases si les deux joueurs ont des cases
            joueurActuel.setCurrentCase(caseSuivante);
            joueurSuivant.setCurrentCase(caseActuelle);

            caseActuelle.setCurrentJoueur(joueurSuivant);
            caseSuivante.setCurrentJoueur(joueurActuel);
        } else if (caseActuelle == null) {
            // Echange lors du premier tour
            joueurActuel.setCurrentCase(caseSuivante);
            joueurSuivant.setCurrentCase(null);
            caseSuivante.setCurrentJoueur(joueurActuel);
        }
    }


    public void deplacerJoueur(Case newCase, Joueur currentJoueur){
        System.out.println(currentJoueur);
        if(newCase == null)
            return;
        if (currentJoueur.getCurrentCase() != null){
            currentJoueur.getCurrentCase().setCurrentJoueur(null);
        }
        if (newCase.getCurrentJoueur() != null){
            alternerPosition(currentJoueur, newCase.getCurrentJoueur());
        }

        currentJoueur.setCurrentCase(newCase);
    }
}
