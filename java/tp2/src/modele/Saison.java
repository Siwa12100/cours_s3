package modele;

import java.util.List;
import java.util.Map;
import java.util.HashMap;

public class Saison {

    private static int numeroSaison;
    Saison instance = this;
    static final Map<Integer, StringBuilder> repertoireSaisons= new HashMap<>();
    public static void initialisationSaisons(){
        repertoireSaisons.put(1, new StringBuilder("Hivern"));
        repertoireSaisons.put(2, new StringBuilder("Prima"));
        repertoireSaisons.put(3, new StringBuilder("Estiu"));
        repertoireSaisons.put(4, new StringBuilder("Devalada"));
    }

    public Saison() {
        initialisationSaisons();
        numeroSaison = 1;
    }

    public Saison(int s) {
        initialisationSaisons();
        numeroSaison = s;
    }

    public static StringBuilder getSaisonActuelle() {
        return repertoireSaisons.get(numeroSaison);
    }

    public static int passerSaisonSuivante(List<Animal> lAnimaux) {
        numeroSaison++;
        if (numeroSaison == 5){
            numeroSaison = 1;
        }
        faireAdapterAnimaux(lAnimaux);
        return numeroSaison;
    }

    public static int getNumSaison() {

        return numeroSaison;
    }

    public static void faireAdapterAnimaux(List<Animal> lAnimaux) {
        for (Animal a: lAnimaux) {
            a.adapterComportementSaison(numeroSaison);
        }
    }
}
