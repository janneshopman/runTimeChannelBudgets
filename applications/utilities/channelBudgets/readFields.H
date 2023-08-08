    IOobject UMeanHeader
    (
        "UMean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    if (!UMeanHeader.typeHeaderOk<volVectorField>(true))
    {
        Info<< "    No UMean field" << endl;
        continue;
    }

    volVectorField UMean
    (
        UMeanHeader,
        mesh
    );

    volSymmTensorField uiujMean
    (
        IOobject
        (
            "uiujMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volTensorField djuiMean
    (
        IOobject
        (
            "djuiMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volScalarField djuidjuiMean
    (
        IOobject
        (
            "djuidjuiMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volVectorField CuiMean
    (
        IOobject
        (
            "CuiMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volScalarField uiCuiMean
    (
        IOobject
        (
            "uiCuiMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volVectorField LuiMean
    (
        IOobject
        (
            "LuiMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volScalarField uiLuiMean
    (
        IOobject
        (
            "uiLuiMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volVectorField GcpMean
    (
        IOobject
        (
            "GcpMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volScalarField uiGcpMean
    (
        IOobject
        (
            "uiGcpMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );
