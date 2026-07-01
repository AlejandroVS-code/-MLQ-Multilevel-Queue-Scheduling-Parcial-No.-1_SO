# Entorno de desarrollo/compilacion para el simulador MLQ
FROM ubuntu:22.04

# Evita prompts interactivos durante la instalacion
ENV DEBIAN_FRONTEND=noninteractive

# g++ (con soporte C++17), make para automatizar la compilacion, gdb para debug
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    gdb \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# El codigo se monta como volumen (ver docker-compose.yml), no se copia aqui,
# para que los cambios que hagas en Windows se reflejen sin reconstruir la imagen
CMD ["/bin/bash"]
