#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <model.h>

class ProcesadorConsulta{
  public:
    static string rutaDB;
    virtual int procesar(Consulta& consulta) = 0;
};

class FiltracionArchivo : public ProcesadorConsulta{
  public:
    int procesar(Consulta& consulta);
};

class FiltracionColumnas : public ProcesadorConsulta{
  public:
    int procesar(Consulta& consulta);
};

class FiltracionFilas : public ProcesadorConsulta{
  public:
    int procesar(Consulta& consulta);
};

class AplicacionClausula : public ProcesadorConsulta{
  public:
    int procesar(Consulta& consulta);
};

class TransformacionJSON : public ProcesadorConsulta{
  public:
    int procesar(Consulta& consulta);
};

#endif