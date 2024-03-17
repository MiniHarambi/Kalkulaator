# Kalkulaator
Tere

Esimest korda kasutades tuleb alla laadida Kalkulaator_GTK4 failid zip failina ja extractida need kõik.
Seejärel tuleb liikuda käsureaga Kalkulator_GTK4 kausta.
Nüüd sisesta järgnevad neli käsku käsureale:

meson --prefix=$PWD/install build

cd build

ninja

ninja install

Esimest korda alla laadides tuleb liikuda tagasi põhikausta (käsuga cd ..). 
Kui aga oled juba põhikaustas, siis sisesta järgnev käsk programmi käivitamiseks:

./install/bin/kalkulaator
