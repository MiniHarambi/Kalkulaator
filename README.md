# Kalkulaator
Dependencies:    
meson   
GTK4   

Esimest korda kasutades tuleb alla laadida Kalkulaator_GTK4 failid zip failina ja extractida need kõik.
Seejärel tuleb liikuda käsureaga Kalkulator_GTK4 kausta.
Nüüd sisesta järgnevad neli käsku käsureale:

meson setup builddir  
cd builddir  
meson compile  
./src/kalkulaator  

