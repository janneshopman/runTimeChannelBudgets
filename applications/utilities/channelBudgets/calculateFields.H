        volSymmTensorField uipujpMean(uiujMean - symm(UMean * UMean));

        volScalarField uxpuxpMean(uipujpMean.component(symmTensor::XX));
        volScalarField uypuypMean(uipujpMean.component(symmTensor::YY));
        volScalarField uzpuzpMean(uipujpMean.component(symmTensor::ZZ));
        volScalarField uxpuypMean(uipujpMean.component(symmTensor::XY));

        volScalarField conv(-(uiCuiMean - (UMean & CuiMean)));
        volScalarField prod(-(uipujpMean && djuiMean));

        volScalarField diff(nu*(uiLuiMean - (UMean & LuiMean)));
        volScalarField diss(-nu*(djuidjuiMean - (djuiMean && djuiMean)));

        volScalarField pDiff(-(uiGcpMean - (UMean & GcpMean)));
