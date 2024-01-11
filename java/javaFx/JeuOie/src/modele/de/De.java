package modele.de;

import java.util.Random;

public class De implements IDe{
    @Override
    public int getValeurRandom() {

        Random random = new Random();
        return random.nextInt(6) + 1;
    }
}
