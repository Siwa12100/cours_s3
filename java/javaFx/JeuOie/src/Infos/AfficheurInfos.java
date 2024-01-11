package Infos;

public class AfficheurInfos {

    private static boolean afficheurActif  = true;
    public static void afficherInfo(String msg) {

        if (afficheurActif) {
            System.out.println(msg);
        }
    }
}
