# Empresa vitivinícola - Software que controle sus líneas de vinos# 


Una empresa vitivinícola lo contrata para realizar un software que controle sus líneas de vinos, las cuales son las siguientes :

de mesa : tiene un precio de 120 pesos por litro y está un año en barrica
premium: tiene un precio de 200 pesos por litro y está 2 años en barrica
especial: tiene un precio de 320 pesos por litro y está 2 años en barrica y 1 en botella.
La empresa guarda la información de su producción en un archivo binario, con el siguiente formato:

       nro : int
       Tipo : char //M(mesa), P (premium), E(especial)
       cantidad_litros: int
       anio_producción: int

(22) Realice el diseño que permita saber la cantidad de litros que se puede vender en un año determinado y el monto que obtendría si se venden todos los litros.

(22) Realice el procedimiento que lea el archivo binario y escriba un archivo de texto con el siguiente formato para los años 2020, 2021, 2022, 2023 :

       Año….litros…... Monto

(22) Realice funciones que permiten saber:

       Los 5 años que se produjeron más litros
       El año que se podrá vender más vino
       El año que se podrá obtener mayor monto de venta.

(18) (no utilice STL) Programe una estructura template que represente una cola. Dicha estructura debe permitir:

       agregar un elemento,
       obtener un elemento.


(16) Indique:
       ¿por qué los template son importantes en un lenguaje de tipado estático?
       ¿cómo implementa c++ el polimorfismo?

Libre: La empresa vitivinícola lo contrata nuevamente ya que formará una nueva línea de venta, dicha línea es un paquete que contiene los 3 tipos de vinos (M(mesa), P (premium) y E(especial)). Diseñe dicha solución y programe un método que permita saber cuántos paquetes se pueden vender en un año determinado.