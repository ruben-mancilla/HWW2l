# H->WW->lvlv (Versiones de prueba)
---------------------------------------------------------
### Este notebook consta de:
-------------------------------------------------------
- El código de análisis [cpp_H_WW_2l_channel_analysis.ipynb](https://github.com/ruben-mancilla/HWW2l/blob/master/cpp_H_WW_2l_channel_analysis.ipynb) que hace toda la seleción y almacena los histogramas de salida

- El encabezado de análisis [make_HWW_objects.h](https://github.com/ruben-mancilla/HWW2l/blob/master/make_HWW_objects.h) que define y da acceso a las variables almacenadas en la muestra de entrada

- El encabezado de histogramas [HWWAnalysisHistograms.h](https://github.com/ruben-mancilla/HWW2l/blob/master/HWWAnalysisHistograms.h) que define los histogramas de salida

- El macro de anáalisis [main_HWWAnalysis.C](https://github.com/ruben-mancilla/HWW2l/blob/master/main_HWWAnalysis.C) que controla las muestras de entrada y su ubicación

- El array [array_sample.C](https://github.com/ruben-mancilla/HWW2l/blob/master/array_sample.C) que es el encargado de asignar los nombres de las muestras a analizar  

- El directorio de salida (Output_HWWAnalysis)[https://github.com/ruben-mancilla/HWW2l/tree/master/Output_HWWAnalysis] es donde se almacena los archivos .root que contienen todos los hitogramas de salida (uno por cada muestra)

- El directorio [Version2](https://github.com/ruben-mancilla/HWW2l/tree/master/Version2) que contiene otra versión del análisis (en estructura) y consta de:  
    - El código de análisis [cpp_H_WW_2l_channel_analysis.ipynb](https://github.com/ruben-mancilla/HWW2l/blob/master/Version2/cpp_H_WW_2l_channel_analysis.ipynb) que hace toda la selección y almacena los histogramas de salidas
    - El encabezado de anáalisis [HWWAnalysis.h](https://github.com/ruben-mancilla/HWW2l/blob/master/Version2/HWWAnalysis.h) que define los histogramas, define y proporciona acceso a las variables almacenadas en las muestras de entrada
    - El encabezado de histogramas [HWWAnalysisHistograms.h](https://github.com/ruben-mancilla/HWW2l/blob/master/Version2/HWWAnalysisHistograms.h) que define el nombre de los histogramas de salida

-------------------------------
Es importante mencionar que la [Version2](https://github.com/ruben-mancilla/HWW2l/tree/master/Version2) sólo es una "mejora" ya que se crean clases para el análisis

PD: Arturo, hago dos versiones como para tener dos estructura de migración y quedarme con la que más te gusten (o hacer todo de nuevo :-) )
