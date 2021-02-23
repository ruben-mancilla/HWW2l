# Análisis del Bosón de Higgs en el Canal de Decaimiento H-->WW*-->eνµν con un Centro de Masa de 13TeV
---------------------------------------------------------
### Este notebook consta de:
-------------------------------------------------------
- El código de análisis [cpp_H_WW_2l_channel_analysis.ipynb](https://github.com/ruben-mancilla/HWW2l/blob/master/cpp_H_WW_2l_channel_analysis.ipynb) que hace toda la seleción y almacena los histogramas de salida

- <b>Directorio [Analysis](https://github.com/ruben-mancilla/HWW2l/tree/master/Analysis)</b>
    - El encabezado de análisis [make_HWW_objects.h](https://github.com/ruben-mancilla/HWW2l/blob/master/Analysis/make_HWW_objects.h) que define y da acceso a las variables almacenadas en la muestra de entrada
    - El encabezado de histogramas [HWWAnalysisHistograms.h](https://github.com/ruben-mancilla/HWW2l/blob/master/Analysis/HWWAnalysisHistograms.h) que define los histogramas de salida así como funciones que permiten llenar, escribir y limpiar los histogramas
   - El macro de anáalisis [main_HWWAnalysis.C](https://github.com/ruben-mancilla/HWW2l/blob/master/Analysis/main_HWWAnalysis.C) que controla las muestras de entrada y su ubicación
   - El array [array_sample.C](https://github.com/ruben-mancilla/HWW2l/blob/master/Analysis/array_sample.C) que es el encargado de asignar los nombres de las muestras a analizar

- <b>Directorio [Plotting](https://github.com/ruben-mancilla/HWW2l/tree/master/Plotting)</b>
    - El encabezado del graficado [Plotting.h](https://github.com/ruben-mancilla/HWW2l/tree/master/Plotting/Plotting.h) que funcine las funciones principales para el graficado
    - El macro de graficado [Plotting.C](https://github.com/ruben-mancilla/HWW2l/tree/master/Plotting/Plotting.C) que se encarga de obtener y guardar los plots finales

- El directorio [Version2](https://github.com/ruben-mancilla/HWW2l/tree/master/Version2) que contiene otra versión del análisis (en estructura). Su diferencia radica en que se crea una clase "HWWAnalysis" (en ellas funciones esenciales) para realizar el análisis
--------------------------------------------------------------------
