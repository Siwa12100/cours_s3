package modele;

import java.util.ArrayList;
import java.util.List;

public class Plateau {

    private List<Case> caseList;

    public Plateau(){
        caseList = new ArrayList<Case>();
    }

    public void addCase(int num){
        caseList.add(new Case(num));
    }

    public Case rechercheCase(Case caseDepart, int nombreDeplacement){
        if (caseDepart == null){
            return caseList.get(nombreDeplacement-1);
        }
        int val = caseDepart.getNum() + nombreDeplacement;

        for (int i = 0; i<caseList.size();i++){
            if(caseList.get(i).getNum() == val){
                return caseList.get(i);
            }
        }
        return null;
    }

    public List<Case> getCaseList() {
        return caseList;
    }

    public int getSizeplateau() {
        return caseList.size();
    }

}
