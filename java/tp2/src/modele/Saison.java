package modele;

import java.util.List;
import java.util.Map;
import java.util.HashMap;

public class Saison {

    private static int numeroSaison;
    private static List<Animal> lAnimaux;
    Saison instance = this;
    static final Map<Integer, StringBuilder> repertoireSaisons= new HashMap<>();
    public static void initialisationSaisons(){
        repertoireSaisons.put(1, new StringBuilder("Hivern"));
        repertoireSaisons.put(2, new StringBuilder("Prima"));
        repertoireSaisons.put(3, new StringBuilder("Estiu"));
        repertoireSaisons.put(4, new StringBuilder("Devalada"));
    }

    public Saison(Animaltheque zoo) {
        initialisationSaisons();
        lAnimaux = zoo.getAnimaux();
        numeroSaison = 1;
    }

    public Saison(int s, Animaltheque zoo) {
        initialisationSaisons();
        lAnimaux = zoo.getAnimaux();
        numeroSaison = s;
    }

    public static StringBuilder getSaisonActuelle() {
        return repertoireSaisons.get(numeroSaison);
    }

    public static int passerSaisonSuivante() {
        numeroSaison++;
        if (numeroSaison == 5){
            numeroSaison = 1;
        }
        faireAdapterAnimaux();
        return numeroSaison;
    }

    public static int getNumSaison() {
        return numeroSaison;
    }

    public static void faireAdapterAnimaux() {
        for (Animal a: lAnimaux) {
            a.adapterComportementSaison(numeroSaison);
        }
    }
}
