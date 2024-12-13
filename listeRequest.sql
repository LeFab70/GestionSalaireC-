-- Liste de requêtes aléatoires
-- ************************************************ -------------------------------

-- Requête 1: Liste des cours (titre) enseigné par chaque enseignant (nom et prénom)
-- ________
select titre,nom,prenom from enseignants inner join cours on enseignants.idProf=cours.enseignant;

-- Requête 2: Liste des cours (titre) suivi par chaque étudiant (nom, prénom) suivie par les filles
-- ________
select titre,nom,prenom from etudiants inner join resultats on etudiants.idEtudiant=resultats.etudiant
inner join cours on resultats.cours=cours.idCours where sexe='F';

-- Requête 3: Liste des résutlats (note obtenue=resultat),cours(titre) pour chaque étudiant (nom,prénom et sexe)
-- ________
select nom,prenom,sexe,titre,resultat from etudiants inner join resultats on etudiants.idEtudiant=resultats.etudiant
inner join cours on resultats.cours=cours.idCours;

-- Defis des autres groupes

-- Équipe 1--	Sélectionnez le nom et prenom tous les étudiants qui ont un résulat 
-- en bas de 60 en ordre de resultat du plus petit petit au plus grand:
select nom, prenom, resultat from etudiants inner join resultats on etudiants.idEtudiant=resultats.etudiant
where resultat <60 order by resultat asc;
-- Sélectionner le nombre d'échecs par étudiant, en ordre du plus grand au plus petit nombre d'echecs
select nom,count(resultat) as totalSousMoyenne from etudiants,resultats where etudiants.idEtudiant=resultats.etudiant
and resultat<60
group by nom
order by totalSousMoyenne desc;

-- other  liste des etudiants avec une sous moyenne
select nom,count(resultat) as totalSousMoyenne from etudiants inner join resultats on etudiants.idEtudiant=resultats.etudiant
and resultat<60
group by nom
having totalSousMoyenne=1
order by totalSousMoyenne desc;

-- Équipe 2 
-- Sortir la liste des étudiants en ordre alphabétique
select concat(nom," ",prenom)as noms,sexe from etudiants order by noms asc; -- si même prenom ranger avec le nom
-- Quelle est la moyenne générale de chacun des cours
select titre,avg(resultat) as moyenne from cours inner join resultats on resultats.cours=cours.idCours
group by titre
order by moyenne desc;

-- Équipe 3 #@ dèjà fait par nous+++++++++
-- Liste des cours (titre) enseigné par chaque enseignant (nom et prénom)
-- Liste des cours (titre) suivi par chaque étudiant (nom, prénom) suivie par les filles 
-- Liste des résutlats (note obtenue=resultat),cours(titre) pour chaque étudiant (nom,prénom et sexe)


