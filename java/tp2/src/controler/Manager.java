package controler;

import interfaces.Afficheur;
import interfaces.Saisisseur;
import modele.Animaltheque;
import modele.Saison;

import java.io.IOException;
import java.util.Scanner;

public class Manager {

    private Saison saison;
    private Saisisseur saisisseur;
    private Afficheur afficheur;
    private Animaltheque animaltheque;
    private Scanner scanner;

    public Manager() {
        scanner = new Scanner(System.in);
        saison = new Saison(4);
        saisisseur = new Saisisseur(saison);
        afficheur = new Afficheur();
        animaltheque = new Animaltheque(saisisseur, afficheur);
    }

    public void lancement() {
        this.menu();
    }

    private void menu() {

        int choix = -1;

        while (choix != 5) {

            System.out.println(" --> Bienvenue au zoo, que souhaitez-vous faire ?");
            System.out.println("\t 1 : Afficher la saison. ");
            System.out.println("\t 2 : Ajouter un animal.");
            System.out.println("\t 3 : Afficher la liste des animaux.");
            System.out.println("\t 4 : Passer à la saison suivante.");
            System.out.println("\t 5 : Quitter le programme.");

            choix = scanner.nextInt();

            switch (choix) {

                case 1 :
                    System.out.println("[Infos] : La saison actuelle est : " +
                            saison.getSaisonActuelle() + "(" + saison.getNumSaison() + ").\n");
                    break;

                case 2 :
                    animaltheque.saisirAnimal();
                    break;

                case 3 :
                    afficheur.afficherAnimaux(animaltheque.getAnimaux());
                    break;

                case 4 :
                    System.out.println("[Infos] : passage à la saison suivante ("
                            + saison.passerSaisonSuivante(animaltheque.getAnimaux()) + ").\n");
                    break;

                case 5 :
                    System.out.println(" --> Fin du programme.");
                    break;

                default :
                    System.out.println("[Erreur] : aucun choix correspondant, saisissez à nouveau...");
                    break;
            }
        }
    }

    /*
    public static void ClearTerminal() {

        switch(os){

            case 0 : // Linux (bash)
                try {
                    ProcessBuilder processBuilder = new ProcessBuilder("clear");
                    processBuilder.inheritIO();
                    Process process = processBuilder.start();
                    int exitCode = process.waitFor();
                    if (exitCode != 0){
                        System.out.println("Une erreur s'est produite lors de l'exécution de la commande clear.");
                    }
                } catch (IOException | InterruptedException e) {
                    e.printStackTrace();
                }
                break;

            case 1 : // Pour Windows mais pas encore fonctionnel...
                //System.out.println(" -> Pas encore de version pour Windows...\n\n");
                try {
                    new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
                } catch (IOException | InterruptedException e) {
                    e.printStackTrace();
                }
                break;
        }
    }

     */
}
