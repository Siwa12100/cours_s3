package modele;

import java.util.Random;

public class Desimple extends De{

    public Desimple(){}

    public void lancer(){
        Random random = new Random();
        int tmp = random.nextInt(6) + 1;
        System.out.println(tmp);
        setVal(tmp);

    }

}
