import controler.VehiculesManager;
import outils.Afficheur;

public class Main {

    public static void test() {
        Afficheur afficheur = new Afficheur();
        String chemin = "test.ser";
        VehiculesManager manager = new VehiculesManager(afficheur, new StringBuilder(chemin));
        //manager.chargerStub();

        //manager.sauvegarderSerial();
        manager.chargerSerial();

        manager.afficherVehicules();
    }

    public static void main(String[] args) {
        //System.out.println("Hello world!");
        test();
    }
}

/* Sujet tp3 :
==============
    A partir d'une application de gestion de véhicule, nous devons être en mesure de sauvegarder et charger des
    véhicules via le mécanisme de serialisation.

    Il faut donc implémenter les fonctionnalités suivantes :

        - Export de la liste de véhicules via le mécanisme de serialisation

        - Import de la liste de véhicules depuis le fichier sérialisé

        - Un prestataire souhaite disposer de notre flotte de véhicules dans un fichier plat,
        donc permette l'export de véhicules sous forme de fichier plat.
 */