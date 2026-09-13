#!/bin/bash
# Uso: ./compilar.sh "Tema4_AnalisisMatricial_I/P42_GaussSistemasPivotacionFisicaCOVID_hacer_alumno"
set -e

if [ -z "$1" ]; then
  echo "Uso: ./compilar.sh <ruta_de_la_practica>"
  exit 1
fi

PRACTICA="$1"

if [ ! -d "$PRACTICA" ]; then
  echo "No existe la carpeta: $PRACTICA"
  exit 1
fi

# 1. Buscar el/los .cbp dentro de la practica
CBPS=(); while IFS= read -r f; do CBPS+=("$f"); done < <(find "$PRACTICA" -name "*.cbp")

if [ ${#CBPS[@]} -eq 0 ]; then
  echo "No se encontro ningun .cbp dentro de: $PRACTICA"
  exit 1
fi

if [ ${#CBPS[@]} -gt 1 ]; then
  echo "Hay varios proyectos .cbp aqui dentro, se mas especifico:"
  printf '  %s\n' "${CBPS[@]}"
  exit 1
fi

CBP="${CBPS[0]}"
CBPDIR="$(dirname "$CBP")"

echo "Proyecto detectado: $CBP"

# 2. Extraer los .cpp listados en el .cbp (rutas relativas al .cbp)
RELSRCS=()
while IFS= read -r f; do RELSRCS+=("$f"); done < <(grep -o 'Unit filename="[^"]*\.cpp"' "$CBP" | sed -E 's/Unit filename="(.*)"/\1/')

if [ ${#RELSRCS[@]} -eq 0 ]; then
  echo "El .cbp no lista ningun .cpp, revisalo a mano."
  exit 1
fi

SRCS=()
for r in "${RELSRCS[@]}"; do
  SRCS+=("$(cd "$CBPDIR" && cd "$(dirname "$r")" && pwd)/$(basename "$r")")
done

echo "Fuentes a compilar:"
printf '  %s\n' "${SRCS[@]}"

# 3. Includes: carpeta del practica, la carpeta del cbp, y cualquier tnt_array que exista
INCLUDES=("-I$PRACTICA" "-I$CBPDIR")
while IFS= read -r d; do
  INCLUDES+=("-I$d")
done < <(find "$PRACTICA" -type d -iname "tnt_array")

# 4. Compilar
BIN="$CBPDIR/programa"
echo
echo "Compilando..."
g++ -std=c++17 -w "${INCLUDES[@]}" "${SRCS[@]}" -o "$BIN"

# 5. Ejecutar desde la carpeta del .cbp (ahi suelen estar los .csv/.png que el programa lee/escribe)
echo "Ejecutando (cwd: $CBPDIR)"
echo "----------------------------------------"
(cd "$CBPDIR" && ./programa)
