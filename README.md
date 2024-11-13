# Manejo de archivos en C
# Proyectos de Lógica de Programación y Manejo de Archivos en C

Este repositorio contiene una serie de proyectos realizados en C, los cuales se enfocan en la manipulación de archivos y lógica de programación. Cada uno de los proyectos tiene un enfoque práctico para resolver problemas reales utilizando estructuras de datos y operaciones con archivos.

## Proyectos

1. **Aerolínea (carpeta airline)**
   - **Descripción**: Este proyecto simula un sistema de gestión de una aerolínea. Se manipulan archivos de pasajeros y vuelos. El sistema permite registrar nuevos pasajeros, buscar información de vuelos y realizar otras operaciones relacionadas con la gestión de vuelos.
   - **Operaciones con Archivos**:
     - Creación de archivos para guardar la información de los pasajeros y vuelos.
     - Búsqueda y actualización de los archivos para manejar las reservas y la disponibilidad de los vuelos.

2. **Curso de Programación (carpeta course)**
   - **Descripción**: Este proyecto simula un sistema de inscripción para un curso de programación. Los usuarios pueden inscribirse al curso y el sistema debe manejar los datos de los inscritos.
   - **Operaciones con Archivos**:
     - Manipulación de archivos para registrar los estudiantes inscritos.
     - Verificación de disponibilidad de cupos y actualización del archivo con la lista de inscritos.

3. **Gestión de Productos (carpeta stockControl)**
   - **Descripción**: Este proyecto maneja un inventario de productos. Se realizan operaciones con el stock de productos, como añadir, eliminar y modificar artículos en el inventario.
   - **Operaciones con Archivos**:
     - Creación y actualización de archivos con información sobre los productos.
     - Operaciones para actualizar el stock de productos y realizar reportes de inventario.

4. **Inscripción de Estudiantes (carpeta students)**
   - **Descripción**: Este proyecto maneja la inscripción de estudiantes en un curso. Si el curso está lleno, los estudiantes no pueden ser inscritos directamente, pero se guardan en un archivo de "interesados" para futuras llamadas.
   - **Operaciones con Archivos**:
     - Registro de estudiantes en el archivo correspondiente si hay cupos disponibles.
     - Si no hay cupos, los datos de los estudiantes se almacenan en un archivo de "interesados" para ser contactados más tarde.

## Requisitos

- **Lenguaje**: C
- **Sistema Operativo**: Compatible con cualquier sistema que tenga un compilador de C (Linux, Windows, macOS).
- **Compilador recomendado**: GCC
