%% Cinematica 4WIR-D: simbolico
clc;clear all;
% 1) Definizione delle variabili simboliche
syms a b L
syms delta1 delta2 delta3 delta4    % angoli δ_i
syms ddelta1 ddelta2 ddelta3 ddelta4 % derivate ṗδ_i
syms v1 v2 v3 v4                    % velocità tangenziali v_i
syms vx vy omega                    % incognite da trovare

% 2) Parametri e vettori di comandi
deltas  = [delta1;  delta2;  delta3;  delta4];
ddeltas = [ddelta1; ddelta2; ddelta3; ddelta4];
vels    = [v1;      v2;      v3;      v4];

% 3) Coordinate dei centri di sterzo nel body frame
centri = [ a,  b;
           a, -b;
          -a,  b;
          -a, -b ];

% 4) Calcolo simbolico delle posizioni delle ruote
Rpos = sym(zeros(4,2));
for i = 1:4
  Rpos(i,:) = centri(i,:) + L*[ cos(deltas(i)), sin(deltas(i)) ];
end

% 5) Costruzione matrici A_par (4×3), b_par (4×1)
A_par = sym(zeros(4,3));
b_par = sym(zeros(4,1));
for i = 1:4
  d   = deltas(i);
  dd  = ddeltas(i);
  xr  = Rpos(i,1);
  yr  = Rpos(i,2);
  % vincolo parallelo
  A_par(i,:) = [ ...
    cos(d), ...
    sin(d), ...
    -yr*cos(d) + xr*sin(d) ];
  b_par(i) = vels(i) + L*dd;
end

% 6) Costruzione matrici A_perp (4×3), b_perp (4×1)
A_perp = sym(zeros(4,3));
b_perp = sym(zeros(4,1));  % tutte zeri
for i = 1:4
  d  = deltas(i);
  xr = Rpos(i,1);
  yr = Rpos(i,2);
  % vincolo perpendicolare
  A_perp(i,:) = [ ...
    -sin(d), ...
     cos(d), ...
     yr*sin(d) + xr*cos(d) ];
  b_perp(i) = 0;
end

% 7) Matrice estesa A (8×3) e vettore b (8×1)
A = [ A_par;  A_perp ];
b = [ b_par;  b_perp ];

% 8) Soluzione in minimi quadrati simbolica
%    (inv(A.'*A)*A.'*b) anziché A\b per mantenere espressione compatta
solSym = simplify( inv(A.'*A) * A.' * b );

%% --- Supponiamo di avere già A e b simbolici e solSym = inv(A.'*A)*A.'*b; ---

% Estrai le componenti
vxSym    = solSym(1);
vySym    = solSym(2);
omegaSym = solSym(3);

% 1) semplificazione base
vx1    = simplify(vxSym);
vy1    = simplify(vySym);
omega1 = simplify(omegaSym);

% 2) semplificazione trigonometrica più aggressiva
vx2    = simplify(vx1, 'Steps', 50);
vy2    = simplify(vy1, 'Steps', 50);
omega2 = simplify(omega1, 'Steps', 50);

% 3) estrai fattori geometrici (a, b, L)
vx3    = factor(vx2, [a, b, L]);
vy3    = factor(vy2, [a, b, L]);
omega3 = factor(omega2, [a, b, L]);

% 4) raggruppa per cosδi e sinδi
vars    = [cos(delta1), sin(delta1), cos(delta2), sin(delta2), ...
           cos(delta3), sin(delta3), cos(delta4), sin(delta4)];
vx_s    = collect(vx3, vars);
vy_s    = collect(vy3, vars);
omega_s = collect(omega3, vars);

% 5) un ultimo simplify per pulizia
vx_final    = simplify(vx_s);
vy_final    = simplify(vy_s);
omega_final = simplify(omega_s);

% Stampa in forma leggibile
disp('v_x = '), pretty(vx_final)
disp('v_y = '), pretty(vy_final)
disp('omega = '), pretty(omega_final)
