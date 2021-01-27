#include "ICL_Program.h"

CICLProgram::~CICLProgram()
{
    clReleaseProgram(ICL_ProgramID);
}

CICLProgram::CICLProgram(cl_context pICL_DeviceContext, cl_device_id pICL_DeviceID, QString pICL_FileName)
{

    //Mapeamento de Erros
    cl_int      ICL_Error;
    //Buffer de ID de Kernels para a criação da Lista de Kernels
    cl_kernel  *ICL_BufferKernelIDS;
    //A OpenCL prevê que podemos carregar uma lista de programas para compilação de Kernels porém
    //por enquanto temos 1 arquivo de Kernel Para cada modulo de utilização.
    char  **pICL_FileBuffer;
    size_t *pICL_SizeBuffer;
    uchar  *pICL_TextoPgm;

    //Cria Arquivo Kernel
    QFile KernelFile(pICL_FileName);

    //Abre arquivo Kernel
    if(!KernelFile.open(QFile::ReadOnly))
    {
        //qWarning() << "Não foi possivel Abrir Arquivo Kernels.";
        return;
    }

    //Mapeia o texto do programa na memória
    pICL_TextoPgm = KernelFile.map(0, KernelFile.size());

    if(!pICL_TextoPgm)
    {
        //qWarning() << "Faltou memória para compilação de Kernel.";
        return;
    }

    //Aloca e Preencje os Buffers para compilação
    pICL_FileBuffer    = new char* [1];
    pICL_SizeBuffer    = new size_t[1];

    pICL_FileBuffer[0] = new char [KernelFile.size()];
    pICL_SizeBuffer[0] = KernelFile.size();

    //Copia o conteudo do texto no primeiro item
    strcpy(pICL_FileBuffer[0],(char *)pICL_TextoPgm);

    //Cria Programa OpenCL
    ICL_ProgramID = clCreateProgramWithSource(pICL_DeviceContext            , //Contexto do Device
                                              1                             , //qtd de arquivos para carga
                                              (const char **)pICL_FileBuffer, //buffer contendo o texto de cada arquivo
                                              pICL_SizeBuffer               , //buffer contendo o tamanho de cada texto
                                              &ICL_Error                    );//saida de erro
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel Criar Programa.";
        exit(1);
    }

    //Compila Programa Criado
    ICL_Error = clBuildProgram(ICL_ProgramID, 1, &pICL_DeviceID ,NULL, NULL, NULL);
    if(ICL_Error != CL_SUCCESS)
    {
        //pega o tamanho da Log(CL so disponibiliza log em caso de erro)
        clGetProgramBuildInfo(ICL_ProgramID, pICL_DeviceID , CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        program_log = new char[log_size+1];
        program_log[log_size] = '\0';

        //Pega a Log Propriamente dita
        clGetProgramBuildInfo(ICL_ProgramID, pICL_DeviceID , CL_PROGRAM_BUILD_LOG,log_size+1, program_log, NULL);

        //qWarning() << program_log;
        exit(1);
    }

    //Recupera o numero de Kernels contido no Programa
    ICL_Error = clCreateKernelsInProgram(ICL_ProgramID, 0, NULL, &ICL_QtdKernels);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel Recuperar o Numero de Kernels disponiveis.";
        exit(1);
    }

    //Aloca o Buffer de Id´s de Kernel
    ICL_BufferKernelIDS = new cl_kernel[ICL_QtdKernels];

    //ATENÇÃO!!! A ORDEM DE CRIAÇÃO DOS KERNELS NO PROGRAMA NÃO DEFINE A ORDEM
    //NO VETOR DE KERNELS.
    ICL_Error = clCreateKernelsInProgram(ICL_ProgramID , ICL_QtdKernels , ICL_BufferKernelIDS , NULL);
    for(cl_uint i = 0; i < ICL_QtdKernels ; i++)
    {
        ICL_Kernels.push_back(new CICLKernel(ICL_BufferKernelIDS[i]));
    }

    //Libera memória mapeada no arquivo
    KernelFile.close();
    KernelFile.unmap(pICL_TextoPgm);

    ICL_ProgramName = pICL_FileName;
}

CICLKernel* CICLProgram::PegaKernelPorNome(QString pICL_Nome)
{
   for(int i=0;i<ICL_QtdKernels;i++)
   {
       QString tNomeFuncao (ICL_Kernels[i]->ICL_NomeFuncao);
       QString tNomeEnviado(pICL_Nome);
       if(tNomeFuncao==tNomeEnviado)return ICL_Kernels[i];
   }

   return NULL;
}
