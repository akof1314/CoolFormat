Declare Auto Function MBox Lib "user32.dll" Alias "MessageBox" (
	ByVal hWnd As Integer,
	ByVal txt As String,
	ByVal caption As String,
	ByVal Typ As Integer) As Integer

<DllImport("KERNEL32.DLL", EntryPoint:="MoveFileW", SetLastError:=True,
	CharSet:=CharSet.Unicode, ExactSpelling:=True,
	CallingConvention:=CallingConvention.StdCall)>
Public Shared Function MoveFile(
	ByVal src As String,
	ByVal dst As String) As Boolean
	' Leave the body of the function empty.
End Function

Module Module1

    Function Main(ByVal cmdArgs() As String) As Integer
        MsgBox("The Main procedure is starting the application.")
        Dim returnValue As Integer = 0
        ' See if there are any arguments.
        If cmdArgs.Length > 0 Then
            For argNum As Integer = 0 To UBound(cmdArgs, 1)
                ' Insert code to examine cmdArgs(argNum) and take
                ' appropriate action based on its value.
            Next argNum
        End If
        
        ' In the following function call, calcSum's local variables 
        ' are assigned the following values: args(0) = 4, args(1) = 3, 
        ' and so on. The displayed sum is 10.
        Dim returnedValue As Double = calcSum(4, 3, 2, 1)
        Console.WriteLine("Sum: " & returnedValue)
        ' Parameter args accepts zero or more arguments. The sum 
        ' displayed by the following statements is 0.
        returnedValue = calcSum()
        Console.WriteLine("Sum: " & returnedValue)
        
        ' Insert call to appropriate starting place in your code.
        ' On return, assign appropriate value to returnValue.
        ' 0 usually means successful completion.
        MsgBox("The application is terminating with error level " &
             CStr(returnValue) & ".")
        Return returnValue
    End Function

    Public Function calcSum(ByVal ParamArray args() As Double) As Double
        calcSum = 0
        If args.Length <= 0 Then Exit Function
        For i As Integer = 0 To UBound(args, 1)
            calcSum += args(i)
        Next i
    End Function

	Private Sub Button_Click(ByVal sender As System.Object,
		ByVal e As System.EventArgs) Handles Button2.Click

		Dim RetVal As Boolean = MoveFile("c:\tmp\Test.txt", "c:\Test.txt")
		If RetVal = True Then
			MsgBox("The file was moved successfully.")
		Else
			MsgBox("The file could not be moved.")
		End If
	End Sub

End Module


'--------------

Imports System.Text
Imports System.Collections.ObjectModel
Imports System.Net

Namespace WpfApplication31
	''' <summary>
	''' Interaction logic for MainWindow.xaml
	''' </summary>
	Partial Public Class MainWindow
		Inherits Window
		Public Sub New()
			InitializeComponent()

			AddHandler Loaded, AddressOf MainWindow_Loaded
		End Sub

		Private Sub MainWindow_Loaded(ByVal sender As Object, ByVal e As RoutedEventArgs)
			TweetList.ItemsSource = _tweets
		End Sub

		Private _tweets As New ObservableCollection(Of Tweet)()

		Private Sub GetTweets_Click(ByVal sender As Object, ByVal e As RoutedEventArgs)
			Dim client As New WebClient()

            AddHandler client.DownloadStringCompleted, AddressOf OnDownloadStringCompleted

			client.DownloadStringAsync(New Uri("http://search.twitter.com/search.atom?q=wpf"))
		End Sub
		
        Private Sub OnDownloadStringCompleted(ByVal s As Object, ByVal ea As Object)
            Dim doc As XDocument = XDocument.Parse(ea.Result)
            Dim ns As XNamespace = "http://www.w3.org/2005/Atom"

            Dim items = From item In doc.Descendants(ns + "entry") _
                        Select New Tweet() With
                               {
                                   .Title = item.Element(ns + "title").Value,
                                   .Image = New Uri(( _
                                        From xe As XElement In item.Descendants(ns + "link") _
                                        Where xe.Attribute("type").Value = "image/png" _
                                        Select xe.Attribute("href").Value).First()),
                                   .Link = New Uri(( _
                                        From xe As XElement In item.Descendants(ns + "link") _
                                        Where xe.Attribute("type").Value = "text/html" _
                                        Select xe.Attribute("href").Value).First())
                                }

            For Each t As Tweet In items
                _tweets.Add(t)
            Next t

            UpdateOverlayIcon()
        End Sub

        Private Class Context
            Public Property CountText() As String
        End Class

		Private Sub UpdateOverlayIcon()
			Dim iconWidth As Integer = 20
			Dim iconHeight As Integer = 20

			Dim context As New Context()
			If _tweets.Count > 99 Then
				context.CountText = "+"
			Else
				context.CountText = _tweets.Count.ToString()
			End If


			Dim bmp As New RenderTargetBitmap(iconWidth, iconHeight, 96, 96, PixelFormats.Default)

			Dim root As New ContentControl()

			root.ContentTemplate = (CType(Resources("OverlayIcon"), DataTemplate))
			root.Content = context

			root.Arrange(New Rect(0, 0, iconWidth, iconHeight))

			bmp.Render(root)

			TaskbarItemInfo.Overlay = CType(bmp, ImageSource)
		End Sub

	End Class

End Namespace
