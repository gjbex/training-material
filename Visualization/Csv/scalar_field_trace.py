try: paraview.simple
except: from paraview.simple import *
paraview.simple._DisableFirstRenderCameraReset()

scalar_field_csv = CSVReader( FileName=['scalar_field.csv'] )

AnimationScene1 = GetAnimationScene()

SpreadSheetView1 = CreateView( "SpreadSheetView" )

DataRepresentation1 = Show()
DataRepresentation1.FieldAssociation = 'Row Data'

AnimationScene1.ViewModules = SpreadSheetView1

TableToStructuredGrid1 = TableToStructuredGrid()

TableToStructuredGrid1.XColumn = 'x'
TableToStructuredGrid1.ZColumn = 'x'
TableToStructuredGrid1.YColumn = 'x'

TableToStructuredGrid1.WholeExtent = [0, 9, 0, 9, 0, 9]
TableToStructuredGrid1.ZColumn = 'z'
TableToStructuredGrid1.YColumn = 'y'

DataRepresentation2 = Show()
DataRepresentation2.FieldAssociation = 'Point Data'

DataRepresentation1.Visibility = 0

RenderView2 = CreateRenderView()
RenderView2.CompressorConfig = 'vtkSquirtCompressor 0 3'
RenderView2.UseLight = 1
RenderView2.CameraPosition = [0.0, 0.0, 7.2677888933284684]
RenderView2.LightSwitch = 0
RenderView2.CameraClippingRange = [5.205111004395183, 9.881805726728395]
RenderView2.Background = [0.31999694819562063, 0.3400015259021897, 0.4299992370489052]
RenderView2.CameraParallelScale = 1.8912877366518224

AnimationScene1.ViewModules = RenderView2

DataRepresentation3 = Show()
DataRepresentation3.EdgeColor = [0.0, 0.0, 0.5000076295109483]
DataRepresentation3.SelectionPointFieldDataArrayName = 'value'
DataRepresentation3.ColorArrayName = ('POINT_DATA', 'value')
DataRepresentation3.ScalarOpacityUnitDistance = 0.3849001794597506
DataRepresentation3.Representation = 'Surface'
DataRepresentation3.ScaleFactor = 0.2

a1_value_PVLookupTable = GetLookupTableForArray( "value", 1, RGBPoints=[0.04978707, 0.23, 0.299, 0.754, 0.506713755, 0.865, 0.865, 0.865, 0.96364044, 0.706, 0.016, 0.15], VectorMode='Magnitude', NanColor=[0.25, 0.0, 0.0], ColorSpace='Diverging', ScalarRangeInitialized=1.0 )

a1_value_PiecewiseFunction = CreatePiecewiseFunction( Points=[0.04978707, 0.0, 0.5, 0.0, 0.96364044, 1.0, 0.5, 0.0] )

Delete(SpreadSheetView1)
DataRepresentation3.ScalarOpacityFunction = a1_value_PiecewiseFunction
DataRepresentation3.LookupTable = a1_value_PVLookupTable

a1_value_PVLookupTable.ScalarOpacityFunction = a1_value_PiecewiseFunction

Delete(DataRepresentation1)
Delete(DataRepresentation2)

Clip1 = Clip( ClipType="Plane" )

Clip1.Scalars = ['POINTS', 'value']
Clip1.ClipType = "Plane"
Clip1.Value = 0.506713755

# toggle the 3D widget visibility.
active_objects.source.SMProxy.InvokeEvent('UserEvent', 'ShowWidget')
RenderView2.CameraClippingRange = [4.791932210011181, 10.401912701568559]

DataRepresentation4 = Show()
DataRepresentation4.EdgeColor = [0.0, 0.0, 0.5000076295109483]
DataRepresentation4.SelectionPointFieldDataArrayName = 'value'
DataRepresentation4.ScalarOpacityFunction = a1_value_PiecewiseFunction
DataRepresentation4.ColorArrayName = ('POINT_DATA', 'value')
DataRepresentation4.ScalarOpacityUnitDistance = 0.4054801330382267
DataRepresentation4.LookupTable = a1_value_PVLookupTable
DataRepresentation4.ScaleFactor = 0.2

DataRepresentation3.Visibility = 0

Clip2 = Clip( ClipType="Plane" )

Clip2.Scalars = ['POINTS', 'value']
Clip2.ClipType.Origin = [0.5, 0.0, 0.0]
Clip2.ClipType = "Plane"
Clip2.Value = 0.506713755

# toggle the 3D widget visibility.
active_objects.source.SMProxy.InvokeEvent('UserEvent', 'ShowWidget')
Clip2.ClipType.Normal = [0.0, 1.0, 0.0]

DataRepresentation5 = Show()
DataRepresentation5.EdgeColor = [0.0, 0.0, 0.5000076295109483]
DataRepresentation5.SelectionPointFieldDataArrayName = 'value'
DataRepresentation5.ScalarOpacityFunction = a1_value_PiecewiseFunction
DataRepresentation5.ColorArrayName = ('POINT_DATA', 'value')
DataRepresentation5.ScalarOpacityUnitDistance = 0.4027307453067008
DataRepresentation5.LookupTable = a1_value_PVLookupTable
DataRepresentation5.ScaleFactor = 0.2

DataRepresentation4.Visibility = 0

Clip3 = Clip( ClipType="Plane" )

Clip3.Scalars = ['POINTS', 'value']
Clip3.ClipType.Origin = [0.5, 0.5, 0.0]
Clip3.ClipType = "Plane"
Clip3.Value = 0.506713755

# toggle the 3D widget visibility.
active_objects.source.SMProxy.InvokeEvent('UserEvent', 'ShowWidget')
RenderView2.CameraClippingRange = [4.80711090950459, 10.382805846176103]

Clip3.ClipType.Normal = [0.0, 0.0, 1.0]

DataRepresentation6 = Show()
DataRepresentation6.EdgeColor = [0.0, 0.0, 0.5000076295109483]
DataRepresentation6.SelectionPointFieldDataArrayName = 'value'
DataRepresentation6.ScalarOpacityFunction = a1_value_PiecewiseFunction
DataRepresentation6.ColorArrayName = ('POINT_DATA', 'value')
DataRepresentation6.ScalarOpacityUnitDistance = 0.34641016151377546
DataRepresentation6.LookupTable = a1_value_PVLookupTable
DataRepresentation6.ScaleFactor = 0.1

DataRepresentation5.Visibility = 0

RenderView2.CameraViewUp = [-0.3568684020625865, -0.18503408106261315, 0.9156458553690998]
RenderView2.CameraPosition = [-4.498541709340031, -4.995132841403623, -2.7627026231655463]
RenderView2.CameraClippingRange = [5.354452887914085, 11.17068475724087]

# toggle the 3D widget visibility.
active_objects.source.SMProxy.InvokeEvent('UserEvent', 'HideWidget')
RenderView2.CameraPosition = [-2.098602907588432, -2.330266335642804, -1.2888211630315165]
RenderView2.CameraClippingRange = [2.513373899593252, 6.409392982448434]
RenderView2.Background = [0.0, 0.0, 0.0]
RenderView2.Background2 = [0.0, 0.0, 0.16470588235294117]

WriteImage('test.pdf')


Render()
