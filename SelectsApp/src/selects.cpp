
#include <controller.h>

int main(){
	
	/* FiltracionArchivo filtracionArchivo = FiltracionArchivo();
	FiltracionColumnas filtroColumnas = FiltroColumnas();
	FiltracionFilas filtroFilas = FiltroFilas();
	AplicacionClausula aplicacionClausula = AplicacionClausula();
	TransformacionJSON transformacionJSON = TransformacionJSON();*/
	int procesadores = 5;
	ProcesadorConsulta* procesadoresConsulta[] = {
		new FiltracionArchivo(),
		new FiltracionColumnas(),
		new FiltracionFilas(),
		new AplicacionClausula(),
		new TransformacionJSON()
	};
	
	string input = "SELECT id,nombre,apellidos FROM Personas"
	               " WHERE edad >= 18 "
				   " ORDER BY nombre ASC";
				   
	Consulta consulta = Consulta(input);
	
	for(int i = 0; i < procesadores; i++){
		ProcesadorConsulta* procesador = procesadoresConsulta[i];
		procesador->procesar(consulta);
		delete procesador;
		
		cout << "Estado actual de las filas: " << endl;
		cout << consulta.toString() << endl;
		cout << "----------------------------" << endl;
	}

    cout << consulta.resultadoJSON << endl;
	
	return 0;
}