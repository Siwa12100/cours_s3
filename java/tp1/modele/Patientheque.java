package modele;

import java.util.ArrayList;
import java.util.List;


class Patientheque {

    private List<Patient> lPatients;

    public Patientheque() {

        lPatients = new ArrayList();
    } 


    public void addPatient(Patient p) {

        lPatients.add(p);
    }
}